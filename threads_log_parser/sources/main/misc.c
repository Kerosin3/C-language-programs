#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1500

void parse_string(FILE* fp);

unsigned serial = 0;


a_url** cr_url_storage(){
	a_url** storage_url = malloc(sizeof(a_url*) );
	*storage_url = calloc(sizeof(a_url), 10); // create 10 urls
	return storage_url;
}

a_url* create_a_url(a_url** storage){
	a_url* t_url = malloc(sizeof(a_url));
	t_url->count = 0;
	t_url->a_str = (void*)0;
	return t_url;
}

void destroy_a_url(a_url* url){
	free(url->a_str);
	free(url);
}



void find_url(char* str){

	const char* st_ptr = str;
	char* part_beg = (void*)0;
	char* part_end = (void*)0;

	st_ptr = strstr(st_ptr,"GET");
	st_ptr+=4;
	part_beg = st_ptr;
	printf("|%s \n",st_ptr);
	if ( *(st_ptr+1) == 32){
		main_page.count++;
	} else {
		printf("extracting the path\n");
		size_t j = 0;
		while ( ( (*st_ptr) != ' ')  ) {
			st_ptr++;
			j++;
		}
		part_end = st_ptr-1;
		printf("1=%s /n",part_beg);
	}

}

void parse_string(FILE* fp){
    unsigned long long total_bytes = 0;
    char buffer[MAX_LEN];

    int main_pagef = 0;
    while (fgets(buffer, MAX_LEN, fp))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] ='\0';
        printf("%s\n", buffer);

	//------------------------------------
	/*
	printf("count = %d\n",main_page.count); 
	st_ptr = buffer;
	part_beg = (void*)0;
	part_end = (void*)0;
	size_t i = 0;
	unsigned long x = 0;
	unsigned long y = 0;
	while ( (st_ptr = strstr(st_ptr,"\"")) ) { // find bytesize
		if (i==1) part_beg = st_ptr+1;
		if (i==2) {
			part_end = st_ptr;
			*part_end = '\0';
			break;
		}
		st_ptr++;
		i++;	
	}
	sscanf(part_beg,"%ld %ld",&x,&y);
	total_bytes+= y;
	printf("x is %d y is %d\n",x,y); // find bytesize */




	}
}
