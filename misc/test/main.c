#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloca.h>
#include <limits.h>
int main(int argc, char *argv[])
{
	const char* some_string = "12345";
	unsigned long long num = 12345678901;
	unsigned __int128 a = 5;
	printf("%llu\n",a*5);
	printf("limits is %llu \n",LLONG_MAX);
	size_t bufsz = snprintf((void*)0, 0,"%llu",num);
	printf("req len is %lu\n",bufsz);
	bufsz++; // for null term
	printf("req len is %lu\n",bufsz);
	char* some_alloc = alloca(bufsz);
	snprintf(some_alloc,bufsz,"%llu",num);
	some_alloc[bufsz]='\0';
	printf("====%s\n",(char*) some_alloc);
	return 0;
}
