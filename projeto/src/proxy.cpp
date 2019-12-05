//
// Created by Rodrigo Demetrio Palma on 04/12/19.
//

#include "header/library.h"
#define MAXRCVLEN 2000
using namespace std;
int proxy(int PORTNUM) {
    extern struct freeMemoryList fml;
    struct sockaddr_in *dest; /* socket info about the machine connecting to us */
    char rmsg[MAXRCVLEN];
    socklen_t socksize = sizeof(struct sockaddr_in);
    cout << "Criando Socket...";
    int ourSocket = createNewSocket(PORTNUM, 1);

    if ((dest = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in))) == NULL) {
        cout << "Erro de alocacao. Abortando\n";
        freeMemory();
        exit(0);
    }
    cout << " Criado!" << endl;
    fml.dest = dest;
    cout << "Aguardando conexão..." << endl;
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
        cout << "Feito.\n";
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
    if(::bind(sckt, (struct sockaddr *)serv, sizeof(struct sockaddr)) == -1){
        std::cerr << "Erro na criação do socket. Escolha outra porta." << std::endl;
        freeMemory();
        exit(1);
    }

    /* start listening, allowing a queue of up to 1 pending connection */
    listen(sckt, parallelConnections);

    return sckt;
}

vector <unsigned char> makeRequest(std::string msg_string) {

    struct sockaddr_in dest;
    struct hostent *hp;
    unsigned char buff;
    //vector <unsigned char> buff (1000);
    int someSocket, len, bytes_read = 0;
    vector <unsigned char> response;

    string host_name = getHostValue(msg_string);
    if((hp = gethostbyname(host_name.c_str())) == NULL){
        fprintf(stderr, "Can't get server's address\n");
        freeMemory();
        exit(1);
    }

    someSocket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&dest, 0, sizeof(dest));                   /* zero the struct */
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)hp->h_addr));
    dest.sin_port = htons(80);                        /* set destination port number */

    if(connect(someSocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in)) == -1){
        printf("Nao foi possivel conectar %s\n", inet_ntoa(dest.sin_addr));
        freeMemory();
        exit(1);
    }
    printf("Conectado no host: %s\n", inet_ntoa(dest.sin_addr));
    write(someSocket, msg_string.c_str(), msg_string.length());

    while((len = read(someSocket, &buff, 1)) > 0){
        response.push_back(buff);
        bytes_read ++;
    }
    printf("%d bytes de resposta recebidos\n", bytes_read);
    close(someSocket);

    return response;
}

std::string getHostValue(std::string msg_string) {

    std::size_t temp, temp2;
    std::string host_name;

    temp = msg_string.find("Host: ");
    temp += strlen("Host: ");
    msg_string.assign( msg_string, temp, string::npos );
    temp2 = msg_string.find("\r\n");
    host_name.assign( msg_string, 0, temp2 );

    return host_name;
}

void freeMemory () {

    extern struct freeMemoryList fml;
    free(fml.serv);
    free(fml.dest);

    fml.serv = NULL;
    fml.dest = NULL;
}