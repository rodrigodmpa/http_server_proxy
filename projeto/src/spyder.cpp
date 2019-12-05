//
// Created by Rodrigo Demetrio Palma on 04/12/19.
//

#include "library.h."
#include "treeLibrary.h"
using namespace std;

/* Return all sources of a sources's sons */
set<string> searchChildren(string url, string baseURL){

    set<string> result;
    if(isReallyHTML(url, baseURL)) {
        cout << endl << "Inspecionando " << url << endl;
        string msg = "GET " + (url) + " HTTP/1.1\r\nHost: " + baseURL + "\r\nConnection: close\r\n\r\n";

        vector<unsigned char> response = makeRequest(msg); // returning response.txt
        /* Converts a vector of unsigned char to a string */
        string response_str;
        for(auto letter:response){
            response_str += letter;
        }
        result.clear();
        buildReference(result, response_str, baseURL);
    }
    return result;
}

/* Cria uma arvore */
Tree generateTree(string baseURL, int levels){


    set <string> root, visited, visited_tree;
    Tree arvore;

    string msg = "GET http://" + baseURL + "/ HTTP/1.1\r\nHost: " + baseURL + "\r\nConnection: close\r\n\r\n";
    cout << msg << "Proceed?" << endl;
    getchar();

    root = searchChildren("/", baseURL);

    Node node_to_insert;
    node_to_insert.src = "/";
    node_to_insert.pai = "\0"; // NULL
    if (levels>0)
        node_to_insert.filhos = root;
    node_to_insert.profundidade = 0;
    node_to_insert.isHTML = true;
    arvore.nodes.push_back(node_to_insert);

    visited.clear();
    visited.insert("/");
    Node node_to_search;
    int profundidade_arvore = 0;
    while(levels>profundidade_arvore){
        auto arvore2 = arvore;
        for(Node node_to_search:arvore2.nodes)
        {
            // Se já tiver sido visitado na árvore anterior (arvore2 é sempre realocada)
            if ((visited_tree.find(node_to_search.src) != visited_tree.end()) or (node_to_search.isHTML==false)){
                continue;
            }
            int cont=0;
            for (string filho:node_to_search.filhos)
            {
                // Node no_pai = findInTree(arvore, node_to_search.src);
                Node node_to_insert;
                node_to_insert.src = filho;
                node_to_insert.pai = node_to_search.src;
                node_to_insert.profundidade = (node_to_search.profundidade + 1);
                set<string> result;
                /* Se o filho ainda não foi visitado e pode possuir filhos */
                if(visited.find(filho) == visited.end())
                {
                    // insere na lista de visitados se ainda não estiver lá
                    visited.emplace(filho);

                    result = searchChildren(filho, baseURL);
                    node_to_insert.filhos = result;
                    if(result.empty()){
                        node_to_insert.isHTML = false;
                    }
                    else{
                        node_to_insert.isHTML = true;
                    }
                }
                    // Se já foi visitado, o nó não irá possuir filhos (pois já foram
                    // listados em algum nó anterior)
                else{
                    node_to_insert.filhos = result; // array vazio
                    node_to_insert.isHTML = false;
                }

                arvore.nodes.push_back(node_to_insert);
                cont++;
                /* Se é o último filho do laço */
                if(cont==((int)node_to_search.filhos.size())){
                    profundidade_arvore = node_to_search.profundidade + 1;
                }

            }
            visited_tree.emplace(node_to_search.src);
        }
        if(arvore2.nodes.size() == arvore.nodes.size()){
            break;
        }
    }

    cout << endl;

    arvore.depth = profundidade_arvore;

    return arvore;
}

bool isReallyHTML(string url, string baseURL) {
    /**
    <Verifica se o cabeçalho da url já foi inspecionado para retornar a informação
    se a url é ou não um HTML.>
    @param url: Url da referência.
    @param baseURL: URL base do domínio desejado.
    @return bool: Indica se é ou não HTML.
    */

    if(mapHTML.find(url) != mapHTML.end()){
        cout << "\nALREADY HAVE " << url << endl;
        return mapHTML[url];
    } else {
        mapHTML[url] = isHTML(url, baseURL);
        return mapHTML[url];
    }
}