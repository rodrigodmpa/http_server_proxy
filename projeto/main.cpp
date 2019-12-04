// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "Client.h"
#include <vector>

#define PORT 8080

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
    int fd, fd2;
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    Client client;

    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);


    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        valread = read(new_socket , buffer, 30000);
        printf("%s\n",buffer);
        std::string str(buffer);

        std::size_t getIndex = str.find("GET");
        std::size_t httpIndex = str.find("HTTP");

        std::string url = str.substr(getIndex + 11, httpIndex - 13);

        int n = url.length();
        char char_array[n + 1];
        strcpy(char_array, url.c_str());

        std::cout << url << std::endl;

        fd2 = client.socket_connect(char_array, 80);
        std::vector<unsigned char> response = client.result(fd2, str);
        unsigned char buff[response.size()];
        for(size_t i = 0; i < response.size(); ++i){
            buff[i] = response[i];
        }

        std::cout << buff << std::endl;
        write(new_socket , buff , int(response.size()));


        shutdown(fd2, SHUT_RDWR);
        close(fd);
        close(new_socket);
    }

    return 0;
}