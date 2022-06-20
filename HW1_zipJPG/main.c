#include <stdio.h>

unsigned f1(unsigned x);

int main(int argc, char *argv[])
{
	unsigned a = 0;
	a = f1(1);
	printf("result is %d \n",a);
	return 0;
}


unsigned f1(unsigned x) {
	if (x<10) return f1((x+1));
	else return x;
}
