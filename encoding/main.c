#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wctype.h>

typedef uint16_t char16_t;
typedef uint8_t char8_t;

#define assignUTF8g(word) \
	_Generic((word), char8_t: utf8_assign1BW, \
			char16_t: utf8_assign2BW,) \
			(word)




unsigned long long total_symbols = 0;

typedef struct { // base utf-8 16 bit wide char
	char8_t zero_byte;
	char8_t first_byte;
} utf8_two_bytes;


void utf8_constr(utf8_two_bytes*); //contructor
void utf8_init(utf8_two_bytes*,char8_t byte0, char8_t byte1);
// use fwire t write one or two bytes
unsigned utf8_write_8(utf8_two_bytes*,FILE*);
unsigned utf8_write_16(utf8_two_bytes*,FILE*);
// assign one or two byte width UTF-8 char
void utf8_assign1BW(utf8_two_bytes*, char8_t byte0);
void utf8_assign2BW(utf8_two_bytes*, char16_t byte01);

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		printf("Please enter filename\n");
		return 0;
	}
	FILE* fp; // all is ok
	//open file
	if ( (fp = fopen(argv[1],"a+b")) == NULL ) {
		printf("error while areating the file, aborting..\n");
		exit(1);
	}
	utf8_two_bytes utf8_word_test;
	utf8_constr(&utf8_word_test);
	//utf8_assign2BW(&utf8_word_test,0x4142);
	char16_t b0 = 0x4142;
        assignUTF8g(&utf8_word_test, b0);
	utf8_write_16(&utf8_word_test,fp);
	//utf8_assign1BW(&utf8_word_test,0x41);
	char8_t b1 = 0x42;
        assignUTF8g( (char8_t) 0x41, b1 );
	utf8_write_8(&utf8_word_test,fp);

	fclose(fp);
	return 0;
}


void utf8_constr(utf8_two_bytes* utf8word){
	total_symbols++; // increment
	utf8word->first_byte = 0x0;
	utf8word->zero_byte= 0x0;	
}

void utf8_init(utf8_two_bytes* utf8word,char8_t byte0, char8_t byte1){
	utf8word -> first_byte = byte0;
	utf8word -> first_byte = byte1;
}
void utf8_assign1BW(utf8_two_bytes* utf8word, char8_t byte0){
	utf8word ->zero_byte = byte0;
	utf8word -> first_byte = 0x00;
}
void utf8_assign2BW(utf8_two_bytes* utf8_word, char16_t byte01){
	unsigned b0 = byte01 & 0xFF; // take lower part
	unsigned b1 = (byte01 >> 8 ) & 0xFF; // take high part
	utf8_word ->zero_byte = b0;
	utf8_word ->first_byte = b1;
}
unsigned utf8_write_8(utf8_two_bytes* utf8_word,FILE* fp){
	char8_t byte0 = utf8_word->first_byte;
	return fwrite(&byte0,sizeof(char8_t),1,fp); // only 8 bits
}
unsigned utf8_write_16(utf8_two_bytes* utf8_word,FILE* fp){
	return fwrite(utf8_word,sizeof(utf8_two_bytes),1,fp); // 16 bits
}


