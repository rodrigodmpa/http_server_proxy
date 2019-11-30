//
// Created by Matheus Feitosa de Castro on 29/11/19.
//

#ifndef HTTP_SERVER_PROXY_CLIENT_H
#define HTTP_SERVER_PROXY_CLIENT_H
#include <string.h>
#include <iostream>




class Client {
    public:              // Access specifier
        int myMethod(char* header);
        int socket_connect(char *host, in_port_t port);
        char* result(int fd);
};


#endif //HTTP_SERVER_PROXY_CLIENT_H
