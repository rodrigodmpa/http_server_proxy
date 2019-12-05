//
// Created by Matheus Feitosa de Castro on 29/11/19.
//

#include "Client.h"
#include "Utils.h"
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <netdb.h>
#define PORT 8228
#define BUFFER_SIZE 1024

int Client::myMethod(char* header) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");

    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "www.sisu.mec.gov.br/", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    printf("Connecting to the server\n");
    if (connect(sock, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Successfully connected to server\n");

    char* hello = "Hello from client";
    printf("Sending message: \"%s\"\n", hello);
    send(sock, header, strlen(header), 0);

    printf("Receiving response from server\n");
    valread = read(sock, buffer, 1024); //Blocked until message is sent from the server
    printf("%s\n", buffer);

    printf("Press any key to exit");
    getchar();
    return 0;
}

int Client::socket_connect(char *host, in_port_t port){
    struct hostent *hp;
    struct sockaddr_in addr;
    int on = 1, sock;

    if((hp = gethostbyname(host)) == NULL){
        std::cout << "Erro host: " << host << std::endl;
        herror("gethostbyname");
        exit(1);
    }
    bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

    if(sock == -1){
        perror("setsockopt");
        exit(1);
    }

    if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
        perror("connect");
        exit(1);

    }
    return sock;
}

std::vector <unsigned char> Client::result(int fd, std::string request) {
    unsigned char buffer;
    std::vector <unsigned char> response;
    write(fd, request.c_str(), request.length()); // write(fd, char[]*, len);

    while(read(fd, &buffer, 1) > 0){
        response.push_back(buffer);
    }

    return response;
}

void Client::proxy() {
    int fd, fd2;
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    Client client;
    Utils utils;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    int enable = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");


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

        std::string url = utils.getUrl(str);

        int n = url.length();
        char char_array[n + 1];
        strcpy(char_array, url.c_str());

        std::cout << "CREATING CONNECTION" << std::endl;
        fd2 = client.socket_connect(char_array, 80);

        std::cout << "MAKING REQUEST" << std::endl;
        std::vector<unsigned char> response = client.result(fd2, str);

        unsigned char buff[response.size()];
        for(size_t i = 0; i < response.size(); ++i){
            buff[i] = response[i];
        }

        std::cout << "SENDING REQUEST" << std::endl << std::endl;
        std::cout << buff << std::endl;
        write(new_socket , buff , int(response.size()));

        shutdown(fd2, SHUT_RDWR);
        close(new_socket);
    }
}