#include <stdio.h>
//#include <stdint.h>
#include <stdlib.h>
#include <wctype.h>
#include <assert.h>
#include <string.h>

//typedef uint16_t char16_t;
//typedef uint8_t char8_t;


#include "multichar.h"
#include  "chars_table.h"

/*#define assignUTF8g(word) \
	_Generic((word), char8_t: utf8_assign1BW, \
			char16_t: utf8_assign2BW,) \
			(word)
*/


/*! \enum name
 *
 *  Detailed description
 */
enum bytewidth {onebyte= 1U, twobyte = 2U};

unsigned long long total_symbols = 0;

typedef struct { // base utf-8 16 bit wide char
	char8_t zero_byte;
	char8_t first_byte;
	unsigned short mark_byte;
} utf8_two_bytes;


void utf8_constr(utf8_two_bytes*); //contructor
void utf8_init(utf8_two_bytes*,char8_t byte0, char8_t byte1);
// use fwire t write one or two bytes
unsigned utf8_write_8(utf8_two_bytes*,FILE*);
unsigned utf8_write_16(utf8_two_bytes*,FILE*);
// assign one or two byte width UTF-8 char
void utf8_assign1BW(utf8_two_bytes*, char8_t byte0);
void utf8_assign2BW(utf8_two_bytes*, char16_t byte01);
char8_t* read_contend_file(FILE*,long unsigned*); 
char8_t* process_koi8(char8_t*i, unsigned long);

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		printf("Please enter filename\n");
		return 0;
	}
	if (argc < 2) {
		printf("you must specify file to write\n");
		return 0;
	}
	if (argc < 2) {
		printf("you must specify readed file encoding\n");
		return 0;
	}

	FILE* fp; // all is ok
	//open file
	if ( (fp = fopen(argv[1],"rb")) == NULL ) {
	//if ( (fp = fopen(argv[1],"a+b")) == NULL ) {
		printf("error while reading the file, aborting..\n");
		exit(1);
	}
	assert ( strlen(argv[2]) != 0 );
	assert ( strlen(argv[2]) <= 25u ); // limit max length
	FILE* fp_w;
	if ( (fp_w = fopen(argv[2],"w+b")) == NULL ) {
		printf("error while creating the file, aborting..\n");
		exit(1);
	}
	//assert ( strlen(argv[3]) <= 25u ); // limit max length
	//char *encoding_specified = argv[3];
	multichar_store storage = multichar_collection_init();
	//printf("----value main:-----%X\n",get_some_multichar(&storage,41).utf8char);
	//printf("----value main:-----%X\n",get_some_multichar(&storage,41).cp1251char);
	//printf("----value main:-----%X\n",get_some_multichar(&storage,41).iso8859char);
	//printf("----value main:-----%X\n",get_some_multichar(&storage,41).koi8char);
	unsigned long cl = 0;
	enum char_type encoding_type = koi;
	/*char8_t gg = 0xE1;
	printf("UTF8:0x%lX \n",find_match(&storage,gg,cp));*/
	char8_t *content_prt = read_contend_file(fp,&cl);
	if (content_prt == NULL) {
		printf("error getting file\n");
		exit(1);
	}
	unsigned long byte_of_file = cl - 1u;
	char16_t* to_write = (char16_t*) calloc(cl,sizeof(char16_t)); //assume all uft8 chars are 2 byte width
	assert (to_write); // should be ok
	char8_t current_readed_char = 0x0;
	rewind(fp_w);
	assert(byte_of_file <= 0xFFFFFFF);
	char8_t* current_position = to_write; // current position in bytes !!!!!!!!!!!!
	unsigned long n_written = 0;
	for (size_t i = 0; i <= byte_of_file; ++i) {
		current_position; // current potion pointer
		current_readed_char = *(content_prt+i);
		char16_t matched = find_match(&storage,current_readed_char,encoding_type);
		printf("readed char is 0x%X ,matched symbol: 0x%lX \n",current_readed_char,matched);
		char8_t byteH_become0 =(char8_t) (matched) ;
		char8_t byteL_become1 =(char8_t) (matched>>8) ;
		//printf("become0 is 0x%X, become1 is 0x%X\n",byteH_become0, byteL_become1);
		if (byteL_become1 == 0x0) { // one byte
			printf("heheh\n");
			//fwrite(&byteH_become0,sizeof(char8_t),1,fp_w); // write one byte
			*(current_position) = byteH_become0; //write one byte
			current_position++; // current potion pointer + 1
			n_written++;
			continue;
		}
		//matched = (byteH_become0 << 8) | byteL_become1;
		
		matched = (matched>>8) | (matched<<8);
		*((char16_t*) current_position) = matched; // assign 2 bytes
		//*(((char8_t*) to_write) +i) = byteH_become0; //write one byte
		printf("matched symbol---: 0x%lX \n",matched);
		//fwrite(&matched,sizeof(char16_t),1,fp_w); // write one byte
		current_position = (((char8_t*) current_position)+2) ; // current potion pointer + 2
		n_written+=2;
		//matched = (matched>>8) | (matched<<8);
		//*(to_write+i) = matched;
	}
	current_position = to_write; // back
	rewind(fp_w);
	fwrite(to_write,n_written*sizeof(char8_t),1,fp_w);

	printf("content length: %lu\n",cl);
	free(content_prt);
	destroy_multichar_store(&storage); // free storage
	free(to_write);
	fclose(fp);
	return 0;
}


void utf8_constr(utf8_two_bytes* utf8word){
	total_symbols++; // increment
	utf8word->first_byte = 0x0;
	utf8word->zero_byte= 0x0;	
	utf8word->mark_byte = twobyte;
}

void utf8_init(utf8_two_bytes* utf8word,char8_t byte0, char8_t byte1){
	utf8word -> first_byte = byte0;
	utf8word -> first_byte = byte1;
	utf8word -> mark_byte = twobyte;
}
void utf8_assign1BW(utf8_two_bytes* utf8word, char8_t byte0){
	utf8word ->zero_byte = ( 0x80 & byte0);// mask out MSB
	utf8word -> first_byte = 0x00;
	utf8word -> mark_byte = twobyte;
}
void utf8_assign2BW(utf8_two_bytes* utf8_word, char16_t byte01){
	unsigned b0 = byte01 | 0xFF; // take lower part
	unsigned b1 = (byte01 >> 8 ) & 0xFF; // take high part
	utf8_word ->zero_byte = b0;
	utf8_word ->first_byte = b1;
	utf8_word -> mark_byte = twobyte;
}
unsigned utf8_write_8(utf8_two_bytes* utf8_word,FILE* fp){
	char8_t byte0 = utf8_word->first_byte;
	return fwrite(&byte0,sizeof(char8_t),1,fp); // only 8 bits
}
unsigned utf8_write_16(utf8_two_bytes* utf8_word,FILE* fp){
	return fwrite(utf8_word,sizeof(utf8_two_bytes),1,fp); // 16 bits
}


char8_t* read_contend_file(FILE* fp,long unsigned* content_length){
	if ((fseek(fp, 0L, SEEK_END))) {
			printf("error reading file\n");
			exit(1);
			}
	long int sz = ftell(fp); // total 
	assert( sz >=0 );
	//sz++; // size +1 NOT
	*content_length = (unsigned long) sz; // change size value
	char8_t *content = (char8_t *) calloc(sz,sizeof(char8_t));
	if (content == NULL){
		printf("error memory allocation\n");
		free(content);
		exit(1);
	}
	rewind(fp);
	fread(content,sz,1,fp);
	return content;

}

char8_t* process_koi8(char8_t* content_to_process,unsigned long size){
	
}
