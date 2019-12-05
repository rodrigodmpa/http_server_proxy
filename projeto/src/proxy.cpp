//
// Created by Rodrigo Demetrio Palma on 04/12/19.
//

#include "library.h"

#define MAXRCVLEN 2000

using namespace std;

int proxy(int PORTNUM) {
    extern struct freeMemoryList fml;
    struct sockaddr_in *dest; /* socket info about the machine connecting to us */
    char rmsg[MAXRCVLEN];
    socklen_t socksize = sizeof(struct sockaddr_in);
    cout << "Tentando criar socket..." << endl;
    int ourSocket = createNewSocket(PORTNUM, 1);

    if ((dest = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in))) == NULL) {
        cout << "Erro de alocacao. Abortando\n";
        freeMemory();
        exit(0);
    }
    fml.dest = dest;
    cout << "Aguardando..." << endl;
    int consocket = accept(ourSocket, (struct sockaddr *)dest, &socksize);
    int len, i = 1000;

    while(--i)
    {
        if((len = read(consocket, rmsg, MAXRCVLEN)) <= 0){
            cout << "Connection close by remote host or some error ocurred. Accepting new connections." << endl;
            close(consocket);
            consocket = accept(ourSocket, (struct sockaddr *)dest, &socksize);
            continue;
        }
        rmsg[len] = '\0';
        if(strstr(rmsg, "POST") != NULL){
            cout << "I am not accepting POST messages. Plese try again" << endl;
            close(consocket);
            consocket = accept(ourSocket, (struct sockaddr *)dest, &socksize);
            continue;
        }
        vector <unsigned char> response = makeRequest(rmsg);
        unsigned char buff[response.size()];
        for(size_t i = 0; i < response.size(); ++i){
            buff[i] = response[i];
        }
        write(consocket, buff, response.size());
        cout << "Done\n";
    }

    close(consocket);
    close(ourSocket);

    freeMemory();
    dest = NULL;

    return EXIT_SUCCESS;
}

int createNewSocket (uint16_t portNum, uint16_t parallelConnections) {

    extern struct freeMemoryList fml;
    struct sockaddr_in *serv; /* socket info about our server */
    int sckt;            /* socket used to listen for incoming connections */

    if ((serv = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in))) == NULL) {
        printf("Erro de alocacao. Abortando\n");
        freeMemory();
        exit(0);
    }
    fml.serv = serv;

    memset(serv, 0, sizeof(struct sockaddr_in));/* zero the struct before filling the fields */
    serv->sin_family = AF_INET;                /* set the type of connection to TCP/IP */
    serv->sin_addr.s_addr = htonl(INADDR_ANY); /* set our address to any interface */
    serv->sin_port = htons(portNum);           /* set the server port number */

    sckt = socket(AF_INET, SOCK_STREAM, 0);

    /* bind serv information to mysocket */
    if((bind(sckt, (struct sockaddr *)serv, sizeof(struct sockaddr))) == -1){
        std::cerr << "Erro na criação do socket. Escolha outra porta." << std::endl;
        freeMemory();
        exit(1);
    }

    /* start listening, allowing a queue of up to 1 pending connection */
    listen(sckt, parallelConnections);

    return sckt;
}

void freeMemory () {

    extern struct freeMemoryList fml;
    free(fml.serv);
    free(fml.dest);

    fml.serv = NULL;
    fml.dest = NULL;
}