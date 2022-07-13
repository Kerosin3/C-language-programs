#include <stdio.h>
#include <stdbool.h>

#define fun1 printfname()
#define pr(x) printf("your result is %d\n",x)

typedef union {
	int i;
	char c;
} some_union;


void printfname(){
	printf("funcname is %s\n",__func__);
}

int main(int argc, char *argv[])
{
	fun1;
	printf(" stdc version is %ld \n",__STDC_VERSION__);


	bool a = true;
	bool b = false;
	pr(a>0 ? pr(a) : pr(b));
	//-------------------------------------
	char input_user[11];
	//fgets(input_user,11,stdin);
	//char buffer[50];
	//snprintf(buffer,50, "blab la sda"); // write to buffer
	//printf("%s\n",input_user); 			//put to std
	//---------------------------------------------------//
	some_union zz;
	const char* some = "hahaha";
	char* b = "hehehe";
	int (*fcall)(char* a) = strcmp(a,some);
	printf("value is %d \n",*fcall(b));
	return 0;
}
