#include <stdio.h>

#define coeff_generic(A,B) \
	_Generic( (A) + (B), \
		       double: coeff_double(A,(double)(B)),\
	       	       float: coeff_float(A,(float)(B)),\
	 	       int:   coeff_int(A,(int)(B)), \
       		       default: coeff_int(A,(int)B))		       

double coeff_double(unsigned a, double b){
	return a*b;
}

int coeff_int(unsigned a,int b){
	return a*b;
}

float coeff_float(unsigned a, float b){
	return a*b;
}

int main(int argc, char *argv[])
{
	unsigned coeff = 5;
	float f0 = 1.5;
	printf("resultis %f \n",coeff_generic(coeff,f0));
	return 0;
}
