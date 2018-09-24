/*	Program Description: This program establishes a server on a local computer. It is prepared to connect with a client from another computer. It executes any single shell command on local computer which is sent from the client. Then, it sends the result back to the client. The server and client must be under same local area network.
	Programmer: Eddie Huang
	Student ID: 104494945
	Date: June 22, 2018 
	*/

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

	char buffer[10000];// buffer to store a shell command from the client.
	int sd, client;// socket descriptor for Server and Client.

	int status;

	socklen_t len;// address length of client socket address.
	struct sockaddr_in servAdd;// Server socket address.
	struct sockaddr_in cliAdd;// Client socket address.

	// Create a Server socket descriptor
	sd = socket(AF_INET,SOCK_STREAM,0);

	// Fill in the domain, IP address, and port number for Server socket address.
	servAdd.sin_family = AF_INET;// Internet domain
	servAdd.sin_addr.s_addr = INADDR_ANY;// local IP address

	/* Port number 55555. Use htons() to convert the port number from processor's byte order into a network byte order.  */
	servAdd.sin_port = htons(54311);

	// Binding the Server socket descriptor with the Server socket address.
	bind(sd, (struct sockaddr*)&servAdd, sizeof(servAdd));

	// Listen the Server socket descriptor, the maximum connection is 10.
	listen(sd,10);

	while(1) {// Use a while loop to keep the Server active even though the client disconnected.
		printf("Waiting for connection ...\n"); // Message of waiting connection.
		len = sizeof(cliAdd);
	
		// Create a client socket descriptor, or in other words, connection socket descriptor.
		client = accept(sd,(struct sockaddr*)&cliAdd,&len);
		printf("Connected.\n");

		// Use a while loop to keep receiving shell commands from the client until the client disconnected.

		while(1) {

			// Read a shell command from the client. If nothing, close the connection socket descriptor and break the loop.
			

			if( read(client,buffer,sizeof(buffer)) <= 0 || buffer[0] == 'q' ) {
				close(client);
				break;
			}

			if(fork() == 0) {// Create a child process to execute the shell command.

				// FOR CLIENT DOWNLOAD FILE FROM THE SERVER
				if(buffer[0] == 'g'){ // if user enters get file , get or sort like , execute this comment 
    				char *p = strtok (buffer, " \t"); // string tokenize it 
    				int i = 0;
    				char *array[2] = {NULL,NULL}; //  stringtokenize two parts of the command into get and the file name 
    
					while (p !=  NULL)
				    {
				        array[i++] = p;
				        p = strtok (NULL, " \t\n");  // this process stringtokenize every single special character subject to space, \n, | 

				    }

					int fd;  // this is the file descriptor 
					int file_size = 0; // this is to get the size of the file 
					char buf[100];    // this is the buffer to store the file content
	     
					fd = open(array[1], O_RDONLY, 0755);
	  //fd2 = open("new.txt", O_WRONLY| O_CREAT | O_TRUNC, 0755);
	
    				while(read(fd, &buf,1) > 0){
	 
	 					file_size++;
	 
	 				}
	 				lseek(fd,0,SEEK_SET);
					read(fd, &buf, file_size);
					write(client,&buf,file_size);
					//write(fd2,&buf,file_size);
					close(fd);
				}else if(buffer[0] == 'p'){ // FOR UPLOAD
              		char *p = strtok (buffer, " \t"); // string tokenize it 
    				int i = 0;
    				char *array[2] = {NULL,NULL}; // 
    
     				while (p !=  NULL)
    				{
						array[i++] = p;
        				p = strtok (NULL, " \t\n");  // this process stringtokenize every single special character subject to space, \n, | 
    				}
    				 

					char buf[1000];				
					int counter = 0;
				 	int fd = open(array[1],O_CREAT | O_TRUNC|  O_WRONLY , 0755);
					char text[1000];

					read(client,&buf,1000);

				 	for(int i = 0; i < 1000; i++){

				 		if(buf[i] == '\0'){
				 			break;
				 		}
				 		text[i] = buf[i];
				 		counter ++;
					}
					 
					 
					write(fd,&text,counter);
			      // printf("%c\n",buf);
					printf("file uploaded\n");
					//write(fd,&buf,10);
					close(fd);
				}
				exit(0);
			}else{
				wait(&status);
			}
		}
	}
	kill(getppid(),SIGTERM);// And terminate its parent process.


	return 0;
}
