#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	int* gaga = calloc(10,sizeof(int));
	gaga[5] = 666;
	printf("result is %d \n",gaga[5]);
	return 0;
}
