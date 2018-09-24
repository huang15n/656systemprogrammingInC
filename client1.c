/*	 */

#include<netinet/in.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<signal.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc,char *argv[]) {

	char size;
	char command_buffer[100]; // this is the command buffer for user to input 
	pid_t pid;
	int serv;
	struct sockaddr_in sAddress;
	if((serv = socket(AF_INET,SOCK_STREAM,0)) < 0)
		{
   fprintf(stderr, "Cannot create socket\n");
exit(1);
	}
	sAddress.sin_family = AF_INET;
	sAddress.sin_addr.s_addr = inet_addr(argv[1]);	
	sAddress.sin_port = htons(55555);
	// Connect to the server.
	connect(serv,(struct sockaddr*)&sAddress,sizeof(sAddress));

		while(1) {
			printf("\n Command:");
			fgets(command_buffer,100,stdin);
			write(serv,&command_buffer,sizeof(command_buffer));
			char *p = strtok (command_buffer, " \t");  
   			 	int i = 0;
				char *commands[2] = {NULL,NULL}; 
    
				while (p !=  NULL)
			    {
			        commands[i++] = p;
			        p = strtok (NULL, " \t\n");  
    			}
  
			
			if(strcmp(commands[0],"getFile") == 0){
				char bbb[1000];
				int count = 0;	 
				int fsize = 0;
				int f = open(commands[1], O_WRONLY| O_CREAT | O_TRUNC, 0755);
				 
				read(serv,&bbb,100);
				write(f,&bbb,100);
				printf("File Downloading Successful\n");
				close(f);
			}else if(strcmp(commands[0],"putFile") == 0){  
					int fsize = 0;
					char bbb[10000];
		 			 
					int f2 = open(commands[1], O_RDONLY, 0755);

	
					read(f2, &bbb, 100);
					write(serv,&bbb,100);
					printf("Uploading Successful\n");
	
					close(f2);
	
				}
			}

	close(serv);
	kill(getppid(),SIGTERM);

	return 0;
}
