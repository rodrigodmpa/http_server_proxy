// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080 

int main(int argc, char const* argv[])
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form 
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	printf("Press any key to connect to the server\n");
	getchar();
	if (connect(sock, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	printf("Successfully connected to server. Press any key to send a message\n");
	getchar();

	char* hello = "Hello from client";
	printf("Sending message: \"%s\"\n", hello);
	send(sock, hello, strlen(hello), 0);

	printf("Receiving response from server\n");
	valread = read(sock, buffer, 1024); //Blocked until message is sent from the server
	printf("%s\n", buffer);

	printf("Press any key to exit");
	getchar();
	return 0;
}