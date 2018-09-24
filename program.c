#include<stdio.h>


int main(){
	int array1[5] = {4,2,1,3,8};
	int max1 = array1[0]; //2
   // 2 * 5.  2 * n
	for(int i = 1; i < 5; i++){
		if(max1 < array1[i]){
			max1 = array1[i];
		}

	}
	printf("the max is %d\n", max1);


	int array2[10] = {4,2,1,3,8,1,2,3,4,5};
	int max2 = array2[0]; //2
   // 2 * 5.  2 * n
	for(int i = 1; i < 10; i++){
		if(max2 < array2[i]){
			max2 = array2[i];
		}

	}
	printf("the max is %d\n", max2);


	return 0;
}