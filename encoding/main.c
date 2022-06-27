#include <stdio.h>
//#include <stdint.h>
#include <stdlib.h>
#include <wctype.h>
#include <assert.h>


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
	FILE* fp; // all is ok
	//open file
	if ( (fp = fopen(argv[1],"rb")) == NULL ) {
	//if ( (fp = fopen(argv[1],"a+b")) == NULL ) {
		printf("error while areating the file, aborting..\n");
		exit(1);
	}
	//utf8_two_bytes utf8_word_test;
//	utf8_constr(&utf8_word_test);
	
	//multichar mchar01 ; // allocate memory for mchar
	//multichar mchars[] ; // allocate array of multichars
	//mchar01 = mchars[0];
	//multichar mchar02 ; // allocate memory for mchar
	//init_multichar(&mchar01);
	//init_multichar(&mchar02);
	//assign_multichar(&mchar01,0xAA,0xAB,0xAC,0xAD);
	//assign_multichar(&mchar02,0xCC,0xCD,0xCE,0xCA);
	//multichar_store storage; //allocate storage
	//init_multichar_store(&storage); //init storage
	//append_to_multichar_store(&storage,mchar01);
	//append_to_multichar_store(&storage,mchar02);
	multichar_store storage = multichar_collection_init();
	printf("----value main:-----%X\n",get_some_multichar(&storage,0).cp1251char);
	//printf("----value main:-----%X\n",get_some_multichar(&storage,1).cp1251char);
	//multichar_store* storage = init_multichar_store(&mchar01);// init array of absract chars
	//assign_multichar(&mchar01,0xAA,0xAB,0xAC,0xAD);
	//append_to_multichar_store(storage,&mchar01);
		
	//utf8_assign2BW(&utf8_word_test,0x4142);
	//char16_t b0 = 0x4142;
        //assignUTF8g(&utf8_word_test, b0);
	//utf8_write_16(&utf8_word_test,fp);
	//utf8_assign1BW(&utf8_word_test,0x41);
	//char8_t b1 = 0x42;
        //assignUTF8g( (char8_t) 0x41, b1 );
	//utf8_write_8(&utf8_word_test,fp);
	unsigned long cl = 0;
	char8_t *content_prt = read_contend_file(fp,&cl);
	if (content_prt == NULL) {
		printf("error getting file\n");
		exit(1);
	}
	for (size_t i = 0; i < 1; ++i) {
		printf("content of[%lu] is %X\n",i,*(content_prt+i));
	}
	printf("content length: %lu\n",cl);
	//destroy_multichar_store(&char00);
	free(content_prt);
	destroy_multichar_store(&storage); // free storage
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
