//
// Created by Rodrigo Demetrio Palma on 29/11/19.
//

#include "SocketClass.h"
SocketClass::SocketClass() {
    m_server_fd = socket(AF_INET, SOCK_STREAM, 0);
}

SocketClass::~SocketClass() {
    if (shutdown(this->m_server_fd,SHUT_RDWR) != -1){
        std::cout << "Conexão fechada." << std::endl;
    }
    if (close(this->m_server_fd) == -1) std::cout << "Não pode fechar o socket." << std::endl;

}

bool SocketClass::Listen(int connect_number){
    int listen_return = listen(this->m_server_fd,connect_number);
    return (listen_return != -1);
}

bool SocketClass::Bind(const int PORT){
    memset(&m_address, 0, sizeof(m_address));
    this->m_address.sin_family = AF_INET;
    this->m_address.sin_addr.s_addr = INADDR_ANY;
    this->m_address.sin_port = htons(PORT);
    int bind_return = bind(m_server_fd, (struct sockaddr *)&m_address, sizeof(m_address));
    return (bind_return != -1);
}

int SocketClass::Accept(){
    int addrlen = sizeof(m_address);
    int socket_descritor = accept(m_server_fd, (struct sockaddr *)&m_address, (socklen_t*)&addrlen);

    return socket_descritor;
}

bool SocketClass::Send(const std::vector<uint8_t> vector, int sock){
    // TODO ver se funciona
    int status = ::send(sock,&vector[0],vector.size(),0);

    return (status != -1);
}

bool SocketClass::Receive(int socket_descritor, std::vector<uint8_t > &vector) {
    uint8_t buffer[2000];
    int valread = recv(socket_descritor , buffer, 2000,0);
    if (valread != -1) return false;
    vector.reserve(valread);
    for(int i = 0;i<valread;i++){
        vector.push_back(buffer[i]);
    }
    return true;
}