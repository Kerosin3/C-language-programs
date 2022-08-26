#include <stdio.h>
#include <stdlib.h>
#include "deamonize.h"
#include <assert.h>
#include <string.h>
#include "parse_settings.h"

#define NUL (void*)0

void destroy_paths(char** pathz);
char** paths_to_analyze();
int main(){
	char *deamon_name = "some_test_deamon";
	deamonize(deamon_name);
	char** pathz = paths_to_analyze();		
	size_t j = 0;
	while (pathz[j]) {
		printf("a path is %s\n",pathz[j]);
		j++;
	}
	destroy_paths(pathz);   	 
	return 0;
}

