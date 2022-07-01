#include "includes.h"
//#define DEBUG
/*#define assignUTF8g(word) \
	_Generic((word), char8_t: utf8_assign1BW, \
			char16_t: utf8_assign2BW,) \
			(word)
 */
enum bytewidth {onebyte= 1U, twobyte = 2U};

typedef struct { // base utf-8 16 bit wide char
	char8_t zero_byte;
	char8_t first_byte;
	unsigned short mark_byte;
} utf8_two_bytes;

size_t strnlen (const char* s, size_t n);
char8_t* read_contend_file(FILE* fp,long unsigned* content_length);
enum char_type decide_encode(const char* input_encoding);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Please enter filename\n");
		return 1;
	}
	if (argc < 3) {
		printf("you must specify file to write\n");
		return 1;
	}
	if (argc < 4) {
		printf("you must specify readed file encoding\n");
		return 1;
	}
	if (argc > 4) {
		printf(" Please specify filename, file to write, encoding of the readed file\n");
		return 1;
	}
	FILE* fp; // all is ok
	//printf("starting..\"%s\"....\n",__LINE__);
	//open file
	if ( (fp = fopen(argv[1],"rb")) == NULL ) {
	//if ( (fp = fopen(argv[1],"a+b")) == NULL ) {
		printf("error while reading the file, aborting..\n");
		exit(1);
	}
	assert ( strnlen(argv[2],25) != 0 );
	assert ( strnlen(argv[2],25) <= 25u ); // limit max length
	FILE* fp_w;
	if ( (fp_w = fopen(argv[2],"w+b")) == NULL ) {
		printf("error while creating the file, aborting..\n");
		exit(1);
	}
	assert ( strnlen(argv[3],10) <= 25u ); // limit max length
	char* encoding_specified = argv[3];
	enum char_type input_encoding;
	input_encoding = decide_encode(encoding_specified);
	if (input_encoding ==  err) {
		printf("please use these ecoding apecifiers: koi,iso,cp \n");
		exit(1);
	}
	multichar_store storage = multichar_collection_init(); // init char collections
	unsigned long cl = 0;
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
	register char8_t* current_position = to_write; // current position in bytes !!!!!!!!!!!!
	register char16_t matched = 0x00;
	unsigned long n_written = 0;
	for (size_t i = 0; i <= byte_of_file; ++i) {
		current_position; // current potion pointer
		current_readed_char = *(content_prt+i);
		matched = find_match(&storage,current_readed_char,input_encoding);
		#ifdef DEBUG
			printf("readed char is 0x%X ,matched symbol: 0x%lX \n",current_readed_char,matched);
		#endif
		char8_t byteH_become0 =(char8_t) (matched) ;
		char8_t byteL_become1 =(char8_t) (matched>>8) ;
		if (byteL_become1 == 0x0) { // one byte
			#ifdef DEBUG
				printf("one-byte char found\n");
			#endif
			*(current_position) = byteH_become0; //write one byte
			current_position++; // current potion pointer + 1
			n_written++;
			continue;
		}
		matched = (matched>>8) | (matched<<8);
		*((char16_t*) current_position) = matched; // assign 2 bytes
		#ifdef DEBUG
			printf("matched symbol---: 0x%lX \n",matched);
		#endif
		current_position = (((char8_t*) current_position)+2) ; // current potion pointer + 2
		n_written+=2;
	}
	current_position = NULL; // back
	rewind(fp_w);
	fwrite(to_write,n_written*sizeof(char8_t),1,fp_w);

	printf("written : %lu characters\n",n_written);
	free(content_prt);
	destroy_multichar_store(&storage); // free storage
	free(to_write);
	fclose(fp);
	fclose(fp_w);
	printf("successful deallocation of resources, program complited\n");
	return 0;
}

enum char_type decide_encode(const char* input_encoding){
	const size_t val = 10; //max size
	char const  *iso_c = "iso";
	char const *koi_c = "koi";
	char const *cp_c = "cp";

	int (*cmp)(const char *,const char *,size_t);
	cmp = strncmp;
	if ( ( cmp(input_encoding,iso_c,val))==0) {
		printf("Analyzing file with ISO-8859-5 encoding\n");
		return iso;
	}
	if ( ( cmp(input_encoding,koi_c,val))==0) {
		printf("Analyzing file with KOI8 encoding\n");
		return koi;
	}
	if ( ( cmp(input_encoding,cp_c,val))==0){
		printf("Analyzing file with CP1251 encoding\n");
		return cp;			
	}  
	return err;
}

char8_t* read_contend_file(FILE* fp,long unsigned* content_length){
	if ((fseek(fp, 0L, SEEK_END))) {
			printf("error reading file\n");
			exit(1);
			}
	long int sz = ftell(fp); // total 
	assert( sz >=0 );
	//sz++; // size +1 NOT ????
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

size_t strnlen (const char* s, size_t n) 
{ 
  const char* found = memchr(s, '\0', n); 
  return found ? (size_t)(found-s) : n; 
}
