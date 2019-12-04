//
// Created by Rodrigo Demetrio Palma on 29/11/19.
//


#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>

#ifndef PROJETO_TR2_1_2018_SOCKETCLASS_H
#define PROJETO_TR2_1_2018_SOCKETCLASS_H


class SocketClass {
private:
    unsigned int m_server_fd;
    struct sockaddr_in m_address;
public:
    SocketClass();
    ~SocketClass();
    bool Listen(int connec_number);
    bool Bind(const int port);
    int Accept();
    bool Receive(int socket_descritor,std::vector<uint8_t > &vector);
    bool Send(const std::vector<uint8_t> vector, int sock);
};


#endif //PROJETO_TR2_1_2018_SOCKETCLASS_H
