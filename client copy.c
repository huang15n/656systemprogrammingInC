/*	Program Description: This program establish a client on a local computer. It connects to a server and send shell command on the server to execute. Then the server sends the result back to this client to print out.
	Programmer: Eddie Huang
	Student ID: 104494945
	Date: June 22, 2018 */

#include<netinet/in.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/signal.h>
#include<fcntl.h>

int main(int argc,char *argv[]) {

	char buffer;// buffer to store the result of an executed shell command from server.
	char cmd[100];// buffer to store a shell command before send to the server.
	pid_t pid;// Process ID for child process.

	int server; // Server socket descriptor.
	struct sockaddr_in servAdd;// Server socket address.

	// Create a socket descriptor for Server in order to use it connect to a specific server.
	server = socket(AF_INET,SOCK_STREAM,0);

	// Fill in the domain, IP address, and port number for Server socket address.
	servAdd.sin_family = AF_INET;// Internet domain.

	// Specific IP address, please check the IP address of the server.
	servAdd.sin_addr.s_addr = inet_addr(argv[1]);

	/* Port number 55555. Use htons() to convert the port number from processor's byte order into a network byte order.  */
	servAdd.sin_port = htons(54311);

	// Connect to the Server.
	connect(server,(struct sockaddr*)&servAdd,sizeof(servAdd));

	/* Child process is used to print out the result from the Server.
	   If the Server is terminated, the while loop is stop and the child process has to terminate the client. */ 

	/*
	if( (pid = fork()) == 0) {

		while(read(server,&buffer,1) == 1) {
			printf("%c",buffer);
		}
	}*/

	/* Parent process is used to receive command from an user.
	   Then, send the command to the Server. */
	//printf("here?");
	//if(pid > 0) {
	//printf("aaa?");
		while(1) {

			printf("\nenter command: ");// Message to ask the user enter a  command.
		
			fgets(cmd,100,stdin);

			// Send the shell command string to the Server.
			write(server,&cmd,sizeof(cmd));
		
			// Waiting the result from Server before next command.

			// FOR DOWNLOAD A FILE FROM THE SERVER
			if(cmd[0] == 'g'){
				char *p = strtok (cmd, " \t"); // string tokenize it 
   			 	int i = 0;
				char *array[2] = {NULL,NULL}; // 
    
				while (p !=  NULL)
			    {
			        array[i++] = p;
			        p = strtok (NULL, " \t\n");  // this process stringtokenize every single special character subject to space, \n, | 
    			}
    

				char buf[1000];
				
				int counter = 0;
				 
				int file_size = 0;
				char character;
				 
				int fd = open(array[1], O_WRONLY| O_CREAT | O_TRUNC, 0755);
				 
               // sleep(2);
   
				char text[1000];

				read(server,&buf,1000);
				 
				for(int i = 0; i < 1000; i++){
				 	if(buf[i] == '\0'){
				 		break;
				 	}
				 	text[i] = buf[i];
				 	counter ++;
				}

				write(fd,&text,counter);
			      // printf("%c\n",buf);
			    		    

				printf("file downloaded\n");
 

				//write(fd,&buf,10);
				close(fd);
			}else if(cmd[0] == 'p'){ // FOR UPLOAD
   					char *p = strtok (cmd, " \t"); // string tokenize it 
   					int i = 0;
    				char *array[2] = {NULL,NULL}; // 

	     			while (p !=  NULL)
	    			{
	        			array[i++] = p;
	        			p = strtok (NULL, " \t\n");  // this process stringtokenize every single special character subject to space, \n, | 
	    			}

	      			int fd2,fd3;
					int file_size = 0;
					char buf[10000];
		 			 
					fd2 = open(array[1], O_RDONLY, 0755);

	// fd2 = open("new.txt", O_WRONLY| O_CREAT | O_TRUNC, 0755);
	
	    			while(read(fd2, &buf,1) > 0){
						 file_size++;
					}
					 

		 			lseek(fd2,0,SEEK_SET);
					read(fd2, &buf, file_size);
					write(server,&buf,file_size);
printf("file uploaded\n");
	// write(fd2,&buf,file_size);
					close(fd2);
	//	close(fd2);
				}
			}
	//}

	close(server);// If the Server is terminated, the child process will close the connection socket descriptor.
	kill(getppid(),SIGTERM);// And terminate its parent process.

	return 0;
}
