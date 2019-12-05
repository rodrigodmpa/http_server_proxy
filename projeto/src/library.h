//
// Created by Rodrigo Demetrio Palma on 04/12/19.
//

#ifndef HTTP_SERVER_PROXY_LIBRARY_H
#define HTTP_SERVER_PROXY_LIBRARY_H

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <streambuf>
#include <experimental/filesystem>
#include <map>


struct freeMemoryList {
    struct sockaddr_in *dest;
    struct sockaddr_in *serv;
};

int proxy(int);
int createNewSocket(uint16_t, uint16_t);
std::vector <unsigned char> makeRequest(std::string);
std::string getHostValue(std::string);
void freeMemory();
std::vector<unsigned char> readBinaryFile(std::string);
std::string readTextFile(std::string);
bool writeFile(std::string, std::vector<unsigned char>);
int inspector(int);
int dump(std::set<std::string>, std::string);
void generateMap(std::map<std::string, std::string>&, std::set<std::string>&, std::string);


#endif //HTTP_SERVER_PROXY_LIBRARY_H
