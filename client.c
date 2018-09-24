#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>



int main(int argc, const char*argv[]){
	char buffer[100];
	int serverSocket;
	socklen_t len;
	struct sockaddr_in serverAddress;

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr= inet_addr(htonl(argv[1]));
	serverAddress.sin_port = 5555;
	connect(serverSocket, (struct sockaddr *)&serverAddress,sizeof(serverAddress));

	read(serverSocket, buffer,100);
	fprintf(stderr,"%s\n", buffer);


}