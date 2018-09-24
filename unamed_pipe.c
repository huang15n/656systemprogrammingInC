#include<unistd.h>
#include<stdio.h>



void child(int *);
void parent(int *);


int main(int argc, const char *argv[]){

  	int fd[2];
  	if(fork() == 0){
  		child(fd);
  	}else {
  		parent(fd);
  	}

	return 0;
}



void parent(int *fd){
	char ch;
	close(fd[1]);
	printf("the child has the mesage \n");
	do {
		read(fd[0], &ch,1);
		printf("%c",ch);
		if(ch == '\n'){
			break;
		}
	}
	while(1);

}


void child(int *fd){
	char message[255] = "this is my data that i am sending";
	close(fd[0]);
	write(fd[1],message, 26);
}