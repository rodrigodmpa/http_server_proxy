//
// Created by Matheus Feitosa de Castro on 04/12/19.
//
#include <string.h>
#include "Utils.h"

std::string Utils::getUrl(std::string request) {
    int index = 0;

    std::size_t httpIndex = request.find("HTTP");

    std::string lastValue = "/";

    if(request[httpIndex - 2] == lastValue[0]) {
        index++;
    }

    std::string reduceUrl = request.substr(0, httpIndex - 1 - index);

    std::string url = reduceUrl.substr(11, reduceUrl.size() - index);

    return url;
}
