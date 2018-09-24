#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include<time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef uint32_t in_addr_t;
void serviceClient(int );

int main(int argc, char *argv[]){
    char *myTime;
    time_t currentUnixTime;
    int sd, client, portNumber;
    socklen_t len;
    struct sockaddr_in servAdd;
	int pid;
    fprintf(stderr, "starting server..\n");


    if(argc != 2){
        fprintf(stderr, "Call model is : %s <Port#>\n", argv[0]);
        exit(0);
    }
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) <0){
        fprintf(stderr, "Could not create socket\n");
        exit(1);
    }

    fprintf(stderr,"socket created\n");
    
    servAdd.sin_family = AF_INET;
    servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
    sscanf(argv[1], "%d", &portNumber);
    servAdd.sin_port = htons((uint16_t)portNumber);
    bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));
    listen(sd, 5);

    fprintf(stderr, "listening to client..\n");

    while(1) {
        client = accept(sd, (struct sockaddr*) NULL, NULL);

        if (fork()==0){
			
            serviceClient(client);
        }
    }
}

void serviceClient(int client) {
	static int count =0;
    fprintf(stderr, "connection accepted..\n");
   // dup2(client, 1);
    //dup2(client, 2);

    while (1) {
				  if(count==2){
                    kill(getpid(), SIGTERM);
                             exit(0);
                                  } 
		char message[100];   				
        read(client, message, 100);
        fprintf(stderr, "received: %s\n", message);
        system(message);
		++count;
    }
    close(client);
    fprintf(stderr, "connection closed.\n");
}

