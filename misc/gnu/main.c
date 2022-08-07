#include <stdio.h>
#include <stdlib.h>

//#define _POSIX_C_SOURCE 200112L

int main(int argc, char *argv[])
{
	printf("posix is %lu \n",_POSIX_C_SOURCE);
	const char msg[] = "hehehe\n";
	write(1,msg,sizeof(msg));
	return 0;
}
