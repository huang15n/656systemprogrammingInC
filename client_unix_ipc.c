#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef uint32_t in_addr_t;


int main(int argc, char *argv[]){

    int SIZE = 500;
    fprintf(stderr,"client program \n");
    char message[SIZE];
    int server, portNumber;
    socklen_t len;
    struct sockaddr_in servAdd;


    if(argc != 3){
        fprintf(stderr, "Call model is : %s <IP> <Port#>\n", argv[0]);
        exit(0);
    }
    if((server = socket(AF_INET, SOCK_STREAM, 0)) <0){
        fprintf(stderr, "Could not create socket\n");
        exit(1);
    }
    fprintf(stderr,"socket created\n");

    servAdd.sin_family=AF_INET;
    sscanf(argv[2], "%d", &portNumber);
    servAdd.sin_port = htons((uint16_t)portNumber);


    fprintf(stderr, "trying to connect port..\n");

    if(inet_pton(AF_INET, argv[1], &servAdd.sin_addr) < 0){
        fprintf(stderr, " inet_pton() has failed\n");
        exit(2);
    }
    fprintf(stderr, "port no. connecting..\n");
    if(connect(server, (struct sockaddr *) &servAdd, sizeof(servAdd)) <0){
        fprintf(stderr, "Connect() failed, exiting\n");
        exit(3);
    }

    fprintf(stderr, "connection at server established\n");
   
    while(1){

        fprintf(stdout, "\n[Enter the command:]");
        fgets(message,100,stdin);
		if (message=='quit'){exit(0);}
        if ( strcmp(message, "") == 0) { continue;}
        write(server, message, strlen(message)+1);

        strcpy(message, "");
        read(server, message, SIZE);
        sleep(1);
        fprintf(stderr, "result of unix command received: \n\n %s", message);
        //fprintf(stderr, "%s", message);
    }
    exit(0);
}
