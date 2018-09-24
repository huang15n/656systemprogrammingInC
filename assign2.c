#include<unistd.h>
#include<fcntl.h>

#include<stdlib.h>
#include<string.h>


/*
name : assignment2
author: eddie huang 
date : 28 May 2018
purpose : this program intends to flip over the image with the designate header and size 
it changes the original picture and make it flexibly fliped once the user runs the program 
the program runs on one dimension array and applied the unix library to open , read and write the file 
the file header is P5 , binary format so can be easily manipulated byte by byte 

*/



int main(int argc, const char* argv[]){

	int fd1 , fd2; // this is the file descriptor for the open file and the destination file 
	char buffer; // this is the temp buffer to caluculate the photo size 
    long int file_size = 0; // this is the file size 
    long int position = 0;    // this is the file position for the reverse image 
    char *file_buffer = NULL;  // this is to define the dynamic array 
    
    char header[] = "P5\n512 512\n255\n";// this is the file header 
    int size_header = strlen(header);  // this is the size of header 
	
	fd1 = open("m1.pgm",O_RDONLY,0755); // open file pgm 

	 
	 while(read(fd1, &buffer,1) > 0){
	 
	 file_size++;
	 
	 }
	 // this is get the size of the file 
     
	 
	//P   5  \n   5   1   2       5   1   2  \n   2   5   5  \n
	

	
    file_buffer = malloc(file_size); // this is to allocate the array memory for the file handling 
	
	lseek(fd1,size_header, SEEK_SET);
	for(int i = 0; i < file_size - size_header; i++){
	
	read(fd1,&file_buffer[i],1);
	
	
	}
	// to read the file with the size of file_size - size header to get the content of the picture 
	
	
	fd2 = open("m1.pgm",O_TRUNC|O_WRONLY,0755);
	// this is to change the file and make read only 
	  
	write(fd2,&header,strlen(header));
	
	lseek(fd2,size_header, SEEK_SET);// set the file header to the position 0 + the size of the file header 
	position = file_size - size_header; // to read the file reversely from the end to the beginning 
    while(position >= 0){ // until it ends the of the buffer array reversely 
    write(fd2,&file_buffer[position],1); // the file will be read from the end 
    position--; 
    
    }
	
	
	
	 
	 
	 close(fd1);
	 close(fd2);	
	 free(file_buffer); 
	 // close the files and free up the memory 
	
	



}



