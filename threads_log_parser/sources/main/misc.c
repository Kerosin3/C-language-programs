#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>

#define MAX_LEN 1500
#define STORAGE_DEF_MAXSIZE 100
void test(void);
void test2(FILE* fp,FILE*);



void parse_string(FILE* fp,storage_url*);
storage_url create_url_storage();
a_url* create_a_url(char* str);
long int append_a_url(a_url* url,storage_url* storage);
long int get_a_urlN(storage_url* storage,char* a_url_to_check);
void destroy_a_url(a_url* url);
void destroy_url_storage(storage_url* storage);
long int append_url_if_nexists(storage_url* storage,char* a_url_str); 
long int append_url_if_nexistsV2(storage_url* storage,char* a_url_str);// use with find  
void storage_expand(storage_url* storage,size_t extend_size);
char* find_url(char str[static 1]);
void get_n_most_urls(storage_url* storage, size_t N);
void merge_structs(storage_url* main_storage,storage_url* a_storage);

void test(){
	storage_url m_storage = create_url_storage();
	srand ((long) time(0)); // define a seed for the random number generator
	for (size_t k=0; k<3560; k++) {
		const char ALLOWED[] = "abcdefghijklmnopqrstuvwxyz1234567890";
		char random[10+1];
		int i = 0;
		int c = 0;
		int nbAllowed = sizeof(ALLOWED)-1;
		for(i=0;i<10;i++) {
		    c = rand() % nbAllowed ;
		    random[i] = ALLOWED[c];
		}
		random[10] = '\0';
		long int ret = append_url_if_nexists(&m_storage,random);
		printf("string is %s, ret is %ld \n",random,ret);
	}
	destroy_url_storage(&m_storage);
}

void test2(FILE* fp,FILE* fp2){
	storage_url m_storage = create_url_storage();
	storage_url s_storage = create_url_storage();
	parse_string(fp,&m_storage);
	printf("storage main size %u \n",m_storage.current_size);
	printf("----------->\n");
	parse_string(fp2, &s_storage);
	printf("storage s size %u \n",s_storage.current_size);
	merge_structs(&m_storage, &s_storage);
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

long int append_a_url(a_url* url,storage_url* storage){
	if (storage->current_size == storage->max_size){
		storage_expand(storage, STORAGE_DEF_MAXSIZE);
		printf("expanded table by 10 entries\n");
	}
//	printf("appended:%s\n",url->a_str);
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

long int append_url_if_nexists(storage_url* storage,char* a_url_str){
	long int N = -1;
	if ( (N = get_a_urlN(storage,a_url_str)) >= 0) return 0; // if exists
	a_url* t_url = create_a_url(a_url_str);
	append_a_url(t_url,storage);
	return 1; // is not exists -> append!
}
long int append_url_if_nexistsV2(storage_url* storage,char* a_url_str){
	long int N = -1;
	if ( (N = get_a_urlN(storage,a_url_str)) >= 0) {
		(*(storage->root_storage)[N]).count++;
		return 0; // if exists
	}
	a_url* t_url = create_a_url(a_url_str);
	append_a_url(t_url,storage);
	return 1; // is not exists -> append!
}

// search a url, if success -> get N, else -> -1;
long int get_a_urlN(storage_url* storage,char* a_url_to_check){
	for (size_t i =0 ; i< storage->max_size; i++) {
		a_url* current_url_p =  ((storage->root_storage)[i]);
		if (!current_url_p) {
			break;
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
 * input - string, ret - 
 */
char* find_url(char str[static 1]){
	char* str_cpy = calloc(sizeof(char), snprintf(0, 0, "%s",str)+1);
	strcpy(str_cpy,str);
	str_cpy[strlen(str_cpy)] = '\0';
	//char* st_ptr = str;
	char* st_ptr = str_cpy;
	char* part_beg = (void*)0;
	char* part_end = (void*)0;
	unsigned long main_page = 0;
	st_ptr = strstr(st_ptr,"GET");
	if (!st_ptr){
		free(str_cpy);
		return (void*)0;
	}
	st_ptr+=4;
	part_beg = st_ptr;
	//printf("|%s \n",st_ptr);
	size_t len = 0;
	if ( *(st_ptr+1) == 32){
		char* ret =calloc(sizeof(char),2 );
		ret[0] = '/';
		ret[1]= '\0';
		if (!ret) {
			printf("error while memory allcation\n");
			exit(1);
		}
		free(str_cpy);
		return ret;
	} else {
		size_t j = 0;
		while ( ( (*st_ptr) != ' ')  ) {
			st_ptr++;
			j++;
		}
		*st_ptr = '\0';
	}
		len = snprintf((void*)0 , 0, "%s",part_beg);
		char* ret =calloc(sizeof(char), ++len);
		strncpy(ret, part_beg,len);
		free(str_cpy);
		return ret; 

}

void merge_structs(storage_url* main_storage,storage_url* a_storage){
	for (size_t index=0; index < (a_storage->max_size);index++) { // work with second storage
		a_url* current_url_p =  ((a_storage->root_storage)[index]);
		if (!current_url_p) { // empty -> end
			continue;
		} 
		// if exists
		char* a_url_str = current_url_p->a_str; // extract string
		unsigned long a_url_str_count = current_url_p->count; // extract N
		long int N = -1;
		if ((N = get_a_urlN(main_storage, a_url_str)) >=0) { //exists -> add count
			((main_storage->root_storage)[N])->count++;
			continue;
		} else{ //not exists
			a_url* t_url = create_a_url(a_url_str); // create new obj
			append_a_url(t_url,main_storage); // append
		}
	}
	printf("------------------>\n");
	printf("storage s size is %u \n",a_storage->current_size);
	printf("storage main size is %u \n",main_storage->current_size);
	destroy_url_storage(a_storage);
	printf("merge done!\n");
}

void parse_string(FILE* fp,storage_url* storage){
    unsigned long long total_bytes = 0;
    char buffer[MAX_LEN];
    size_t ii = 1;
    int main_pagef = 0;
    while (fgets(buffer, MAX_LEN, fp))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] ='\0';
	//printf("i is %lu \n",ii);
        //printf("%s\n", buffer); print page
	char* a_url_str = find_url(buffer);
	if (!a_url_str) continue;
	int appnded = append_url_if_nexistsV2(storage,a_url_str);
	//(appnded) ? printf("---------\n") : printf("add count!\n");	
	free(a_url_str);
	ii++;
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
	printf("x is %d y is %d\n",x,y); // find bytesize 
	*/	



	}
}
long int extract_bytes(char[static 1]){
	
}
/*
int compare_urls_n(const void *a,const void *b){
	a_url* x = (a_url*) a; 
	a_url* y = (a_url*) b; 
	return x->count - y->count; 
}

void get_n_most_urls(storage_url* storage, size_t N){
	qsort(void *base, size_t nmemb, size_t size, __compar_fn_t compar)
			
}
*/
