#include "string_parse.h"
#include <stdio.h>


signed long long parse_string(int fd,storage_url* storage, storage_url* storage_refer){
    char* buffer = calloc(sizeof(char), MAX_LEN);
    if (!buffer) {
	    printf("error while memory allocation\n");
	    exit(1);
    }
    size_t ii = 1;
    signed long long total_bytes = 0;
    FILE* fp;
    printf("working with %d fd\n",fd);
    if  (!(fp=fdopen(fd, "rb"))){
	printf("error while opening fd\n");
	exit(1);
    }
    while (fgets(buffer, MAX_LEN, fp))
    {
        buffer[strcspn(buffer, "\n")] ='\0';
	ii++;
	//----------------------------------//
	char* a_url_str = find_url(buffer);
//	printf("string №%ld cont %s\n",ii,a_url_str);
//	printf("string №%ld \n",ii);
	if (!a_url_str) continue;
	int appended_url = append_url_if_nexistsV2(storage,a_url_str);
	free(a_url_str);
	//---------------------------------//
	signed long bs = -1;
	total_bytes += extract_bytes(buffer);
	//---------------------------------//
	char* ext_refer = extract_refer(buffer);
//	printf("refer:%s\n",ext_refer);
	int appended_refer = append_url_if_nexistsV2(storage_refer,ext_refer);
	free(ext_refer);

	memset(buffer,'\0',MAX_LEN);
	}
    free(buffer);
    return total_bytes;
}
long int extract_bytes(char buf[static 1]){
	char* part_beg = (void*)0;
	char* part_end = (void*)0;
	char* st_ptr = buf;
	st_ptr = strstr(st_ptr,"GET");
	if (!st_ptr) return -1;
	long int x,y;
	size_t i = 1;
	while ( (st_ptr = strstr(st_ptr,"\"")) ) { // find mark
		if (i==1) part_beg = st_ptr+1;// find first
		if (i==2) {
			break;
		}
		st_ptr++;
		i++;	
	}
	sscanf(part_beg,"%ld %ld",&x,&y);
	//printf("x is %ld y is %ld\n",x,y); // find bytesize 
	return y;
}
char* extract_refer(char buf[static 1]){
	char* part_beg = (void*)0;
	char* part_end = (void*)0;
	char* st_ptr = buf;
	size_t i = 1;
	while ( (st_ptr = strstr(st_ptr,"\"")) ) { // find mark
		if (i != 4) part_beg = st_ptr+1;// find first "
		if (i==5) {
			break;
		}
		st_ptr++;
		i++;	
	}
	st_ptr = buf;
	while ( (st_ptr = strstr(st_ptr,"\"")) ) { // find mark
		if (i==10) { //find second "
			part_end = st_ptr;
			break;
		}
		st_ptr++;
		i++;	
		part_end = st_ptr;
	}

	size_t len = part_end - part_beg;
	char* refer = calloc(sizeof(char), len+1);
	memcpy(refer, part_beg, len);
	refer[len] = '\0';
	return refer;
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

