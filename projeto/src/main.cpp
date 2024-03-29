//
// Created by Rodrigo Demetrio Palma on 05/12/19.
//

#include "header/library.h"

using namespace std;

int main(int argc, char* argv[]){

    int value=0;
    string baseURL;
    int portnum;

    if (argc == 3 && !strcmp(argv[1],"-p")){
        try
        {
            portnum = atoi(argv[2]);
            if(portnum == 0){
                cout << "ERRO: a porta deve ser um inteiro." << endl;
                return 1;
            }
            cout << "INFO: porta escolhida: " << portnum << endl;
        }
        catch(const exception& e)
        {
            cerr << e.what() << '\n';
        }

    } else if (argc == 1) {
        portnum = 8228;
    } else {
        cout << "Como usar: aracne or aracne -p [portnum]" << endl;
        return 1;
    }
    cout << "----------------\n";
    cout << "(1) Proxy       |\n(2) Inspector   |\n(3) Spider      |\n(4) Dump        |\n";
    cout << "----------------\n";
    cout << "\n Escolha uma opção: ";
    while(true){
        scanf("%d", &value);
        if(value== 1 || value == 2 || value == 3 || value == 4) break;
        cout << " Valor incorreto." << endl;
        cout << " Escolha uma opção: ";
    }

    if(value==3 || value ==4){
        cout << " Forneca um dominio valido ex. www.ba.gov.br: ";
        cin >> baseURL;
        cout << endl;
    }

    switch (value) {
        case 1:
            proxy(portnum);
            break;
        case 2:
            inspector(portnum);
            break;
        case 3:
            spider(baseURL);
            break;
        case 4:
            makeDump(baseURL);
            break;
    }
    return 0;
}
