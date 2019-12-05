//
// Created by Rodrigo Demetrio Palma on 04/12/19.
//

#ifndef HTTP_SERVER_PROXY_SPYDER_H
#define HTTP_SERVER_PROXY_SPYDER_H

#include <string.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <streambuf>
#include <experimental/filesystem>
#include <map>

class Node{


public:

    // Data Members
    std::string src;
    std::string pai;
    std::set<std::string> filhos;
    int profundidade;
    bool isHTML;
};

class Tree{

public:
    std::vector<Node> nodes;
    int depth;
    std::map<int,std::set<std::string>> printed_on_level;

    /* Finds a specific node in Tree by it's source and level */
    Node findInTree(std::string src, int level){

        for(std::vector<Node>::iterator it=(this->nodes).begin(); it!=(this->nodes).end(); ++it){
            if(((*it).src == src) && ((*it).profundidade==level)){
                return *it;
            }
        }
        Node j;
        return j;
    }

    /* Finds all nodes on that level in Tree */
    std::vector<Node> seekLevel(int level){

        std::vector<Node> listNodeLevel;
        for(Node i : (this->nodes) ){
            if (i.profundidade == level){
                listNodeLevel.push_back(i);
            }
        }
        return listNodeLevel;
    }

    /* Converts a vector of Nodes to a vector of strings */
    std::set<std::string> treeToVector(){

        std::set<std::string> srcSet;
        for(Node i:(this->nodes)){
            srcSet.emplace(i.src);
        }
        return srcSet;
    }

    std::string printFilhos(Node node){

        std::string msg = "";
        /* é pulado se já foi printado naquele nível */
        std::set<std::string> printed_l = (this->printed_on_level)[node.profundidade];
        if(printed_l.find(node.src)!=printed_l.end()){
            return msg;
        }
        for(int i=node.profundidade; i!=0; i--){
            std::cout << "\t";
            msg += "\t";
        }
        if(node.isHTML){
            if(node.filhos.size() >0){
                std::cout << (node.src) << " =>" << std::endl;
                msg += node.src + " =>\n";
                for(std::string it:node.filhos){
                    Node filho = this->findInTree(it, node.profundidade+1);
                    /* se tiver filhos e não for o último nível, será printado em outro momento */
                    if((filho.filhos.size() == 0) || (filho.profundidade==(this->depth))){
                        for(int i=filho.profundidade; i!=0; i--){
                            std::cout << "\t";
                            msg += "\t";
                        }
                        std::cout << filho.src << std::endl;
                        msg += filho.src+"\n";
                        (this->printed_on_level)[filho.profundidade].emplace(filho.src);
                    }
                }
            }
        }
        else{
            std::cout << node.src << std::endl;
            msg += node.src + "\n";
        }

        return msg;
    }

    /* Print the tree */
    void printTree(){

        std::vector<Node> nodes;
        std::string texto;
        std::ofstream file;
        file.open("arvore_hipertextual.txt");
        int p=0;
        while(p<(this->depth)){
            nodes = this->seekLevel(p);
            for(Node i: nodes){
                texto = printFilhos(i);
                file << texto;
            }
            p++;
        }
        file.close();
    }
};

Tree generateTree(std::string, int);
std::map<std::string, bool> mapHTML;

std::set<std::string> searchChildren(std::string, std::string);
Node findInTree(std::vector<Node>, std::string, int);
std::vector<Node> seekLevel(std::vector<Node>, int);
void printTree(std::vector<Node>, int);
std::set<std::string> treeToVector(std::vector<Node>);

void buildReference(std::set<std::string> & ,std::string, std::string);
bool isHTML(std::string, std::string);

#endif //HTTP_SERVER_PROXY_SPYDER_H
