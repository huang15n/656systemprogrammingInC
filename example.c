#include <pthread.h>
#include <stdio.h>
#include<unistd.h>
int main(){
    printf("hello\n");
    alarm(1);
    sleep(2);
    printf("this is me\n");
	
}