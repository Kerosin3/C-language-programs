#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

void func1(){
	volatile x = 5;
	volatile y = 666;
//	printf("current func is %s\n",__func__);
//	printf("current line is %d\n",__LINE__);
	void* array[4096];
	size_t size = backtrace(array,4096);
	backtrace_symbols_fd(array,size,1);
	puts("");
}
 
int main(int argc, char *argv[]){


	func1();
	return 0;
}

