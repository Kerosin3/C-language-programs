#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
//#include "spookyhash/src/spookyhash_api.h"
#include "BSD_strings.c"

#define DEBUG
#define MAX_LORD_LENGTH 25

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
	while ( (( some_word = find_a_word(fp_r) ).word)  ){ // WHILE NOT NULL
		//some_word = find_a_word(fp_r);
		printf("%d,your word is \"%s\"\n",END_REACHED,(char*) (some_word.word));
	}

	fclose(fp_r);
	return 0;
}

word_pointers find_a_word(FILE* fp){
	uint8_t read_char = 0;
	long int beg = 0;
	long int end = 0;
	int width = 0;
	uint8_t* a_word = (uint8_t*) calloc(MAX_LORD_LENGTH+1,sizeof(uint8_t) );
	beg = ftell(fp);// set beginning of the word
	word_pointers out;
	out.begin = beg; 
	unsigned i = 0;
	do {
		if (feof(fp)) {
		#ifdef DEBUG
			printf("EOF REACHED!!\n");
		#endif
			END_REACHED = 1;
			//out.word = a_word; 
			break;
		}
		fread(&read_char,1,1,fp); // read one byte and move cursor
		a_word[i]=read_char;	
		i++;
		#ifdef DEBUG
			//printf("readed 0x%X, is space =%X \n",read_char,isspace(read_char));
		#endif
	} while ( !(isspace(read_char))  ); //not space or EOF
	a_word[i-1]='\0'; // set null symbol
	end = ftell(fp);
	out.end = end; 
	width = end - beg; // no need to add extra for null
	a_word = (END_REACHED) ? NULL :  realloc(a_word,i*sizeof(uint8_t)); // i size is ok
	out.word = a_word;
	#ifdef DEBUG
		printf("space chr  has been found!\n");
		printf("beg=%lu,end=%lu \n",out.begin,out.end);
	#endif
		return out;
	
}
/*
void* extract_a_word(word_pointers word_points){
	int beginning = word_points.begin;
	int endings = word_points.end;
	endings--; // discard spac
	unsigned width = (endings - beginning)+1; // add null symbol	

}*/
