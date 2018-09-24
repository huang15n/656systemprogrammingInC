#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include <signal.h> 
#include<stdlib.h>
#include <sys/wait.h>

int main(int argc,char *argv[]) {

	char command_buffer[10000]; 
	int server_socket; 
	int client_socket; 
	int status;
	socklen_t length; 
	struct sockaddr_in server_address;
	struct sockaddr_in client_address; 
	server_socket = socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family = AF_INET; 
	server_address.sin_addr.s_addr = INADDR_ANY; 
	server_address.sin_port = htons(55555);
	bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
	listen(server_socket,4);

	while(1) { 
		printf("Waiting for connection ...\n");  
		length = sizeof(client_address);
		client_socket = accept(server_socket,(struct sockaddr*)&client_address,&length);
		printf("Successfully Connected.\n");


		while(1) {
			if( read(client_socket,command_buffer,sizeof(command_buffer)) <= 0) {
				kill(getppid(),SIGTERM); 
				close(client_socket);
				break;
			}

			if(fork() == 0) { 
				char *p = strtok (command_buffer, " \t\n");  
				int counter = 0;
				char *command[2] = {NULL,NULL}; 
				while (p !=  NULL)
				{
					command[counter] = p;
					p = strtok (NULL, " \t\n");  
					counter++;
				} 
				if(strcmp(command[0],"getFile") == 0){ 
					char file_buffer[10000];     
					int file_descriptor = open(command[1], O_RDONLY, 0755);
					read(file_descriptor, &file_buffer, 100);
					write(client_socket,&file_buffer,100);
					close(file_descriptor);
				}else if(strcmp(command[0],"putFile") == 0){ 
					char file_buffer[1000]; 		
					int file_descriptor = open(command[1],O_CREAT | O_TRUNC|  O_WRONLY , 0755);
										
					read(client_socket,&file_buffer,1000);
					write(file_descriptor,&file_buffer,1000);
					printf("file uploaded\n");
					close(file_descriptor);
				}else {
					printf("\nplease enter getFile and putFile\n");
				}
				exit(0);
			}else{
				wait(&status);
			}
		}
	}
	kill(getppid(),SIGTERM); 


	return 0;
}
