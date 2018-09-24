#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

/*
parent is used to redirect the output from screen to the file descriptor 
the function intakes file descriptor , two arguments to process the shell command 
using exclp and execute the bash command line user provided 
*/


void parent(int *fd , char *array1, char *array2){
	 int status;
	 pid_t pid;
	 close(fd[1]); // close write 
	 dup2(fd[0],0); // redirect the read 
	 close(fd[0]); // close read 
 
	 execlp(array1,array1,array2, NULL); // get the arguments and execute 
	 

}


/*
the child function runs similarly as parent, but within one flag to detect if the character of - exists in the second argument 
in this case , for example ps -e | wc -c contains four characters whilst date | wc -c includes three 
i have already stringtokenize the pipe thereby the provided arguments can be found by this particular - character 


*/
void child(int *fd, char *array1, char *array2,int flag){
	close(fd[0]); // close reading 
	dup2(fd[1],1); // redirect writing 
	close(fd[1]); // close writing 
	int status;
	pid_t pid;
	   
	if(flag == 0){
	execlp(array1,array1,NULL);  // date | wc -c 
}else {
	execlp(array1,array1,array2,NULL);//ps -e | wc -c 

}
 



}
 
	 
 

int main(int argc, const char *argv[]){
	 char buf[100]; // to define the buffer 
    int i = 0; // count of element 
    int fd[2]; // file descriptor for pipe 
  while(1){
  i = 0;
     fgets(buf,100,stdin); // get user input 
   // scanf("%s",buf);
    char *p = strtok (buf, " |\n"); // string tokenize it 
    
    char *array[4] = {NULL,NULL,NULL,NULL}; // four string arrays 
    pid_t pid1,pid2;  // process id 
    int status; // wait status 
   
    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, " |\n");  // this process stringtokenize every single special character subject to space, \n, | 

    }

 
 if(pipe(fd) == -1) {exit(1);}
else {
 
 
    if(array[2]== NULL ){ // this is to take only two arguments 
    	 
    	 // fork 
    	    	 if( (pid1 = fork()) == 0){   
     	execlp(array[0],array[0],array[1],0); // it 
        }else {
        	wait(&status);

        }
      

      }else {
      	
      
      	
      	if( (pid2 = fork()) == 0){
      		//

      		if(strchr(array[1],'-')){ // if the second argument contains - 
      			child(fd,array[0],array[1],1);  // contains first and second argument 
      		}else {
      			child(fd,array[0],array[0],0); // contains one argument 
      		}
      	 
      	}
      	else {
      		 
      		 
      		 	if(strchr(array[1],'-')){
      			parent(fd,array[2],array[3]); // if the second one is the argument contains - 
      		}else {
      			parent(fd,array[1],array[2]); //  if the second one is not the argument 
      		}
        
      		       
      			}
 
     }

}

}




}

/*


*/