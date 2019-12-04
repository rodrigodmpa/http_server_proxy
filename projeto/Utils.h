//
// Created by Matheus Feitosa de Castro on 04/12/19.
//

#ifndef HTTP_SERVER_PROXY_UTILS_H
#define HTTP_SERVER_PROXY_UTILS_H


#include <string>

class Utils {
    public:
        std::string getUrl(std::string request);
        std::string charToString(char *value);
        char* stringToChar(std::string value);
};


#endif //HTTP_SERVER_PROXY_UTILS_H
