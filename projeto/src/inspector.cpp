//
// Created by Rodrigo Demetrio Palma on 04/12/19.
//

#include "library.h"

#define MAXRCVLEN 2000

struct freeMemoryList fml;
using namespace std;

std::vector<unsigned char> readBinaryFile(string filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<unsigned char> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<unsigned char>(file),
               std::istream_iterator<unsigned char>());

    return vec;
}

std::string readTextFile(string path)
{

    string result;
    ifstream ifs(path, ios::binary);
    string str(istreambuf_iterator<char>{ifs}, {});

    return str;
}

bool writeFile(string path, vector<unsigned char> dados){

    ofstream fout(path, ios::out | ios::binary);
    fout.write((char*)&dados[0], dados.size() * sizeof(unsigned char));
    fout.close();

    return true;
}