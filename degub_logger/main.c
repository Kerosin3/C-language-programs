#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#define SOME() func1(__LINE__);

typedef enum log_level{
	debug,info,warning,error
} log_level;

void func1(int linen){
	void* array[4096];
	printf("line n is %d\n",linen);
	size_t size = backtrace(array,4096);
	backtrace_symbols_fd(array,size,1);
	puts("");
}

void test_fun(){
	printf("we are here\n");
	char* kaka = malloc(10);
	SOME();
}

FILE* write_to_log(char filename[static 1]){
	FILE* log_file;
	log_file = fopen(filename,"a+" );
	if (!log_file) {
		printf("error while opening the log file\n");
		exit(1);
	}
	return log_file;
}

int main(int argc, char *argv[]){

	SOME();
	test_fun();
	
	return 0;
}

