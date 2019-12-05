// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "Client.h"
#include "Utils.h"
#include <vector>

#define PORT 8228

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{

    Client client;
    client.proxy();
    return 0;
}