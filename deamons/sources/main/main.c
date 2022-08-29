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
	_Bool denable = false;
	const char** pathz = paths_to_analyze();		
	denable = if_deamon();
	if (denable){
		printf("enabling demonization\n");
		deamonize(pathz);
//		start_server(pathz);
	}
	size_t j = 0;
	/*
	while (pathz[j]) {
		printf("a path is %s\n",pathz[j]);
		printf("size of file is %u \n",calc_filesize(pathz[j]));
		j++;
	}
	destroy_paths(pathz);   	 */
	//destroy_paths(pathz);  	 
	return 0;
}

