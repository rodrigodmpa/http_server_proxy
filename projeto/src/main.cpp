//
// Created by Rodrigo Demetrio Palma on 05/12/19.
//

#include "library.h"

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
                cout << "port must be an integer." << endl;
                return 1;
            }
            cout << "port choosed: " << portnum << endl;
        }
        catch(const exception& e)
        {
            cerr << e.what() << '\n';
        }

    } else if (argc == 1) {
        portnum = 8228;
    } else {
        cout << "Usage: aracne or aracne -p [portnum]" << endl;
        return 1;
    }

    cout << "(1) Proxy\n(2) Inspector\n(3) Spyder\n(4) Dump\n\n Escolha uma opção: ";
    while(true){
        scanf("%d", &value);
        if(value== 1 || value == 2 || value == 3 || value == 4) break;
        cout << " Valor incorreto." << endl;
        cout << " Escolha uma opção: ";
    }

    if(value==3 || value ==4){
        cout << " Forneca um dominio valido: ";
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
            spyder(baseURL);
            break;
        case 4:
            makeDump(baseURL);
            break;
    }
    return 0;
}
