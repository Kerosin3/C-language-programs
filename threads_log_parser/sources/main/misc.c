#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#define MAX_LEN 1500
#define STORAGE_DEF_MAXSIZE 10
void parse_string(FILE* fp);

unsigned serial = 0;

storage_url create_url_storage();
a_url* create_a_url(char* str);
int append_a_url(a_url* url,storage_url* storage);
void test(void);
int get_a_urlN(storage_url* storage,char* a_url_to_check);
void destroy_a_url(a_url* url);
void destroy_url_storage(storage_url* storage);

void storage_expand(storage_url* storage,size_t extend_size);

void test(){
	storage_url m_storage = create_url_storage();
	char* str_sss = "hahaha";
	char* str_s0 = "oneone";
	a_url* some_url = create_a_url(str_sss);
	a_url* some_url1 = create_a_url(str_s0);
	append_a_url(some_url,&m_storage );
	append_a_url(some_url1,&m_storage );
	storage_expand(&m_storage,5);
	printf("size new is %u \n",m_storage.max_size);
	destroy_url_storage(&m_storage);
}

storage_url create_url_storage(){
	a_url** main_pointer = calloc(sizeof(a_url*),STORAGE_DEF_MAXSIZE);
	if (!main_pointer ){
		printf("error while memory allocation!\n");
		exit(1);
	}
	storage_url main_storage;
	main_storage.current_size = 0;
	main_storage.max_size = STORAGE_DEF_MAXSIZE;
	main_storage.root_storage = main_pointer;
	return main_storage;
}

void storage_expand(storage_url* storage,size_t extend_size){
	if (extend_size <= 0) {
		printf("pass next size more than 0\n");
		exit(1);
	}
	a_url** new_root = realloc(storage->root_storage,sizeof(a_url*)*((storage->max_size)+extend_size));
	if (!new_root){
		printf("error while reallocation\n");
		exit(1);
	}
	for (size_t j=storage->max_size; j< (storage->max_size + extend_size) ; j++) {
		new_root[j] = (void*)0;
	}
	storage->root_storage = new_root;
	storage->max_size += extend_size;

}

void destroy_url_storage(storage_url* storage){
	for (size_t i =0 ; i< storage->max_size; i++) {
		a_url* current_url_p =  ((storage->root_storage)[i]);
		if (!current_url_p) {
			continue;
		}
		free(current_url_p->a_str);
		free(current_url_p);
		}

	free(storage->root_storage);
}

int append_a_url(a_url* url,storage_url* storage){
	if (storage->current_size == storage->max_size){
		storage_expand(storage, 10);
		printf("expanded table by 10 entries\n");
	}
	(storage->root_storage)[storage->current_size] = url;
	storage->current_size+=1;
	return 0;	
}

a_url* create_a_url(char* str){
	a_url* t_url = malloc(sizeof(a_url));
	t_url->count = 0;
	size_t str_leng = strlen(str);
	char* string_str = calloc(1,str_leng+1);
	if (!string_str) {
		printf("error while memory allocation!\n");
		exit(1);
	}
	strcpy(string_str,str);
	string_str[str_leng] = '\0';
	t_url->a_str = string_str;
	return t_url;
}

int get_a_urlN(storage_url* storage,char* a_url_to_check){
	for (size_t i =0 ; i< storage->max_size; i++) {
		a_url* current_url_p =  ((storage->root_storage)[i]);
		if (!current_url_p) {
			continue;
		}
		char* current_url =  (*(storage->root_storage)[i]).a_str;
		if (!(strcmp(current_url,a_url_to_check))) return i;
		}
	return -1;
	}

void destroy_a_url(a_url* url){
	free(url->a_str);
	free(url);
}

/*

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
	/*



	}
}
*/
