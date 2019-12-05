//
// Created by Rodrigo Demetrio Palma on 04/12/19.
//

#include "library.h"
using namespace std;

int dump(set<string> requests, string baseURL) {


    string request;
    vector <unsigned char> serverResponse;
    string systemCommand;
    string filename;
    string foldername = "mkdir -p " + baseURL;
    ofstream file;
    map <string, string> mapRefs;

    system(foldername.c_str());

    generateMap(mapRefs, requests, baseURL);

    for(set<string>::iterator itr = requests.begin(); itr != requests.end(); ++itr){
        if((*itr)[0] != '/'){
            request = "GET /" + (*itr) + " HTTP/1.1\r\nHost: " + baseURL + "\r\nConnection: close\r\n\r\n";
            if ((*itr).find_last_of('/') == string::npos){
                foldername = baseURL + "/";
            } else {
                foldername = baseURL + "/" + (*itr).substr(0, (*itr).find_last_of('/'));
            }
            systemCommand = "mkdir -p " + foldername;
            filename = baseURL + string("/") + (*itr);
        } else {
            request = "GET " + (*itr) + " HTTP/1.1\r\nHost: " + baseURL + "\r\nConnection: close\r\n\r\n";
            foldername = baseURL + (*itr).substr(0, (*itr).find_last_of('/'));
            systemCommand = "mkdir -p " + foldername;
            filename = baseURL + (*itr);
        }
        cout << "Inside dump function\n" << request << "Proceed" <<endl;
        serverResponse = makeRequest(request);
        string response_str;
        for(auto letter:serverResponse){
            response_str += letter;
        }
        response_str = cutHead(response_str);

        if(!isReallyHTML(*itr, baseURL)) {
            system(systemCommand.c_str());
            cout << "tryning to write to folder: " << foldername << endl;
            file.open(filename, ofstream::binary);
            if(file.is_open()){
                file << response_str;
                file.close();
            } else {
                cout << "Unable to open file. Proceed?" << endl;
                getchar();
            }
        } else {// procurar href, src e trocar as referencias
            string name = mapRefs[(*itr)];
            name = baseURL + "/" + name;
            fixRefs(response_str, mapRefs);//necessario arrumar as referencias

            cout << "\n\tTryning to write to file: " << name << endl;
            file.open(name, ofstream::binary);
            if(file.is_open()){
                file << response_str;
                file.close();
            } else {
                cout << "Unable to open file. Proceed?" << endl;
                getchar();
            }
        }
    }
    return EXIT_SUCCESS;
}

void generateMap(map<string, string> &mapRefs, set<string> &requests, string baseURL) {


    for(set<string>::iterator i = requests.begin(); i != requests.end(); ++i){
        if(!isReallyHTML(*i, baseURL)){//se nao for html mapeie dele para ele mesmo
            if((*i).front() == '/'){
                mapRefs[*i] = (*i).substr(1);
            } else {
                mapRefs[*i] = *i;
            }
        }
        else if((*i).compare("") == 0){//eh uma referencia quebrada
            continue;
        } else if((*i).compare("/") == 0){//eh a raiz "/" -> index.html
            mapRefs[*i] = "index.html";
        } else if((*i).find("/") == string::npos) {//eh um html e nao possui / -> (nome.html)
            mapRefs[*i] = (*i) + ".html";
        } else if (((*i).find_last_of("/")) != string::npos) {//eh um html e possui /
            string buff = (*i);
            if(buff.back() == '/') {//ultimo caractere eh uma "/" -> substituir por .html
                buff.back() = '.';
                buff += "html";
            } else {
                buff += ".html";
            }
            buff = buff.substr(buff.find_last_of("/") + 1);
            mapRefs[*i] = buff;
        }
    }
}