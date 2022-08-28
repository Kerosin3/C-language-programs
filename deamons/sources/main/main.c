#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "deamonize.h"
#include <assert.h>
#include <string.h>
#include "parse_settings.h"
#include "deamon_magic.h"

#define NUL (void*)0


int main(){
	char *deamon_name = "some_test_deamon";
	//deamonize(deamon_name);
	_Bool denable = false;
	char** pathz = paths_to_analyze(&denable);		
	if (denable){
		printf("enabling demonization\n");
		test();
	}
	size_t j = 0;
	while (pathz[j]) {
		printf("a path is %s\n",pathz[j]);
		j++;
	}
	destroy_paths(pathz);   	 
	return 0;
}

