#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
//#include "spookyhash/src/spookyhash_api.h"
#include "BSD_strings.c"
#include "hash_f.h"


#define DEBUG
#define MAX_WORD_LENGTH 25

typedef struct {
	long int begin;
	long int end;
	char* word;
} word_pointers;

word_pointers find_a_word(FILE* fp);

void* extract_a_word(word_pointers);
unsigned END_REACHED = 0;

int main(int argc, char *argv[])
{
        //char u_input[21];
	//fgets(u_input,21,stdin);
	//unsigned len = strnlen(u_input,20);
	//printf("you entered:%s, length is %d\n",u_input,len);
	FILE* fp_r;
	if ((fp_r = fopen(argv[1],"rb")) == NULL) {
		printf("error opening file, aborting...\n");
		exit(1);
	}
	rewind(fp_r);
	word_pointers some_word;
	unsigned long long hash_val = 0;
	while ( (( some_word = find_a_word(fp_r) ).word)  ){ // WHILE NOT NULL
		//some_word = find_a_word(fp_r);
		printf("%d,your word is \"%s\"\n",END_REACHED,(char*) (some_word.word));
		hash_val=calc_hash((char*) (some_word.word)); // memory is assigned here
		free(some_word.word);
		printf("value of has is %llu\n",hash_val);
	}
	test0();
	fclose(fp_r);
	//free(some_word.word);
	return 0;
}

word_pointers find_a_word(FILE* fp){
	uint8_t read_char = 0;
	long int beg = 0;
	long int end = 0;
	int width = 0;
	beg = ftell(fp);//set beginning to current position
	word_pointers out;
	out.begin = beg; 
	unsigned i = 0;
	do {
		if (feof(fp)) {
		#ifdef DEBUG
			printf("EOF REACHED!!\n");
		#endif
			end = ftell(fp);
			out.end = end; 
			END_REACHED = 1;
			out.word = NULL; 
			return out;
		}
		fread(&read_char,1,1,fp); // read one byte and move cursor
		i++;
		#ifdef DEBUG
			//printf("readed 0x%X, is space =%X \n",read_char,isspace(read_char));
		#endif
	} while ( !(isspace(read_char))  ); //not space or EOF
	i--; //decrement last i, i+1 == total elements need
	uint8_t* a_word = (uint8_t*) calloc(i+1,sizeof(uint8_t) );// one for NULL TERMINATOR
	if (!(a_word)) {
		printf("ERROR WHILE ASSIGNING WORD, WHAT IS ITS LENGTH???\n");
		exit(1);
	}
	uint8_t* ptr_a_word = a_word;
	signed convert = ~i ; // convert = (-i + 1) ONE CHAR MORE
	//printf("value of if is %u, negative is %d \n",i,convert);
	fseek(fp,convert,SEEK_CUR); // set cursor back
	for (size_t j = 0; j < i; ++j) { //read content 0.1.2..6
		fread(&read_char,1,1,fp); // read one byte 
		ptr_a_word[j] = read_char;
	}
	ptr_a_word[i]='\0'; // set null symbol
	end = ftell(fp);
	out.end = end; 
	width = end - beg; // no need to add extra for null
	a_word = (END_REACHED) ? NULL :  a_word; // i size is ok
	out.word = a_word;
	do {//skip whitepaces
		fread(&read_char,1,1,fp);
	} while (!(isspace(read_char)));
	#ifdef DEBUG
		printf("space chr  has been found!\n");
		printf("beg=%lu,end=%lu \n",out.begin,out.end);
	#endif
		return out;
	
}
