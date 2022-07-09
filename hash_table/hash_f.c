#include "hash_f.h"
#define IS_UNSIGNED(t) ((t)~1 > 0)
unsigned long long calc_hash(uint8_t* input_string){
	//printf("hash - %s \n",(char*) input_string);
	printf(" is unsigned??? %d\n",IS_UNSIGNED(char));
	if (sizeof(char) != sizeof(uint8_t)) {
		printf("platform error!,aborting...\n");
		return 0;
	}
	char* str_ptr =(char*) input_string;
	//printf("len of string %d\n",strnlen(str_ptr,25)); // 25 - max word length 
	size_t str_size= strnlen(str_ptr,25); // size of analyzed string
	char* to_analyze[str_size+1];// plus null terminator
	strlcpy(to_analyze,str_ptr,26);
	size_t l_to_analyze = strnlen(str_ptr,25);
	printf("copied string is %s, its length is %d \n",to_analyze,strnlen(str_ptr,25));
	unsigned long long temp_c= 0;
	for (size_t i = 0; i < l_to_analyze; ++i) {// not includes null terminator
		temp_c+=( ((uint8_t) to_analyze[i] ) * pow(((unsigned) SALT),i)  ); // unicode is always 7 byte with leading zero
		//printf("value is 0x%X, your hash is %llu\n",(uint8_t) to_analyze[i],temp_c);
	}
	return temp_c;
	
}


