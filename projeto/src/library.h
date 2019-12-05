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


int proxy(int);


#endif //HTTP_SERVER_PROXY_LIBRARY_H
