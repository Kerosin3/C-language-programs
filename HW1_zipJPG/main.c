#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <inttypes.h>
#include <stdint.h>
// Autor - Alex V
// Description: jpg-zip filename finder v1.0.

#define DEBUG 	  0 
#define MAX_WORD  8 // max bit patter width, min = 2


signed long long read_bytes(FILE*,unsigned,unsigned, ...); //retuns last byte number
unsigned long find_valid_jpg(FILE*);// __attribute__ ((nwarn_wint_conversion));
unsigned long find_zip_filename(FILE*); //__attribute__ ((Nwarn_wint_conversion));

// return unused
signed long extract_filename(FILE*, unsigned long offset);
//------------------------------------
unsigned global_offset = 0x0;
//------------------------------------
//
int main(int argc, char *argv[])
{
	unsigned long long jpg_end = 0x0;
	unsigned long first_signature_zip = 0x1;
	unsigned n_files= 0;
	//printf("%d\n",__STDC_VERSION__);
	if (argc <= 1) {
		printf("Please specify a valid jpg file\n");
		return 0;
	}
	FILE* fp; // all is ok
	//open file
	if ( (fp = fopen(argv[1],"rb")) == NULL ) {
		printf("error while opening the file, aborting..\n");
		exit(1);
	}
	fp = fopen(argv[1],"rb");
	if (!(jpg_end = find_valid_jpg(fp))) {// find whether this is a valid jpg file
		printf("jpg signatures has not been found, you passed not a valid jpg file, exiting...\n");
		exit(1);
		}
	while ( ( first_signature_zip = find_zip_filename(fp) ) ){ // repead find zip header signature and extract a filename till EOF
		if (DEBUG) printf("first zip signature offset is: 0x%lX\n",first_signature_zip);
		extract_filename(fp,first_signature_zip); // extract filename and add to a global offset
		n_files++;
	}// while not EOF
	global_offset = 0x0;
	fclose(fp);
	return 0;
}

signed long extract_filename(FILE* fp,unsigned long offset) {
		offset+=1; // read from the next position
		static unsigned nn_calls = 0;
		if (DEBUG) printf("current offset is %lX \n",offset);
		const unsigned filename_length = 2; // for length, not for filename itself
		signed long offset_signature = 0x0;
		const unsigned long len_offset =  0x16;  // 0x10 + 0xA - 4
		unsigned length_of_filename = 0x0 ;
		offset += len_offset; // add offseti to filename len field
		unsigned char buf[filename_length];
		fseek(fp,offset,SEEK_SET); //set position to len filename field
		fread(buf,1,filename_length,fp); // read 2 bytes for filename
		for (size_t i = 0; i < filename_length; ++i) {
			if (DEBUG) printf("filename length 0x%X\n",buf[i]);		
		}
		length_of_filename  = buf[0] + (buf[1] << 8); //add to total filename len
		unsigned char filename_chars[17]; // filename 17 byles max
		if (DEBUG) printf("length of filename is %d \n",length_of_filename);
		fseek(fp,offset+4,SEEK_SET);  // filename fiels is just 2 bytes next
		fread(filename_chars,1,length_of_filename,fp); 
		if (DEBUG)for (size_t i = 0;  i < length_of_filename; ++ i) {
			printf("char: 0x%X %c \n",filename_chars[i],filename_chars[i]);
		}
		printf("name of a %u'th compressed file: ",nn_calls+1);
		for (size_t i = 0; i < length_of_filename; ++i) {
			printf("%c",filename_chars[i]);
		} printf("\n");
		global_offset = offset + 0xF + 0x7; // set global adress to extra fiel offse
		offset_signature = global_offset;
		if (DEBUG) printf("next offset is %x \n",global_offset);
		nn_calls++;
		return offset_signature;
		//unsigned char filename[18]; // max filename
		//fseek(fp,offset,SEEK_SET); //set position to ..
			
}
unsigned long find_zip_filename(FILE* fp){
	if (DEBUG) printf("searching first local file zip signature\n");
	unsigned const*const header_start[4] = {
		0x50u,
		0x4Bu,
		0x03u,
		0x04u,
	};
	signed long long signarute_offset = 0x0;
	signarute_offset = read_bytes(fp,global_offset,4,header_start[0],header_start[1],header_start[2],header_start[3]);
	if (signarute_offset >= 0){
		if (DEBUG) printf("found valid zip signature at offset: 0x%llX\n",signarute_offset);
		return (unsigned long) signarute_offset; // return first signature offset
	} else {
		if (DEBUG) printf("not valid zip signature has been found\n");
		return 0;
	}
	return 0;

}

unsigned long find_valid_jpg(FILE* fp) {
	printf("searching valid jpg image\n");
	unsigned const*const jpg_start[2] = {
		0xFFu,
		0xD8u,
	};
	unsigned const*const jpg_end[2] = {
		0xFFu,
		0xD9u,
	};
	unsigned long out_func = 0;
	signed long long  out = 0;
	if ( (out = read_bytes(fp,global_offset,2,jpg_start[0],jpg_start[1]))  > 0 ) {
		printf("found valid jpg signature at: 0x%llX\n",out);
	} else {
		printf("valid jpg signature has not been found, aborting..\n");
		return 0; // beginning not found
	}
	if ( (out = read_bytes(fp,global_offset,2,jpg_end[0],jpg_end[1]))  > 0 ) {
		printf("found valid end jpg signature at: 0x%llX\n",out);
		printf("----------------------ok---------------------\n");
		out_func = (unsigned) (out);
		return out_func; // rerutn end position  
		}
	else {
		printf("not valid jpg image has been found\n");
		return 0;// end not found
		}
}
signed long long read_bytes(FILE* fp,unsigned skip, unsigned n_width, ...){
	va_list ap;
	va_start(ap,n_width);
	static unsigned n_calls = 0;
	if (n_width <= 1 ) return -1; // not valid
	if (n_width > MAX_WORD) return -1; // more than max
	unsigned char searched_comp[MAX_WORD] = {0}; //searched bytes
	uint64_t searched_pattern = 0x0000000000000000; // all zeros
	for (size_t i = 0; i < n_width ; ++i) { // assign bytes to array
		searched_comp[i] = (unsigned char) va_arg(ap, int); // INT????
		if (DEBUG) printf("you paseed 0x%X\n",searched_comp[i]);
	}
	uint64_t whole_word = 0x0000000000000000; // all zeros
	unsigned long stop_byte= 0;
	size_t t = 1;
	searched_pattern = searched_comp[0]; // combine consequitive bytes
		do {
			searched_pattern = searched_pattern << 8; // hope it works
			searched_pattern = searched_pattern | searched_comp[t] ;
			t++;
		} while (t != n_width);
	if (DEBUG) printf("searched pattern is 0x%lX\n",searched_pattern);


	unsigned char* buffer = (unsigned char*) malloc(sizeof(unsigned char)*n_width); //allocate for buf
	unsigned long offset_byte = 0;
	//rewind(fp); //start from the start...
	while (!(feof(fp))) { //read from start
		if (DEBUG) printf("i= %lu\n",offset_byte);
		fseek(fp, offset_byte + skip ,SEEK_SET); // set 0,1,2,3 byte
		fread(buffer, 1, n_width ,fp);  // read byte * n width
		for (size_t i = 0; i < n_width; ++i) {
			//printf("readed: 0x%X\n",buffer[i]);
		}
		size_t c = 1;
		whole_word = buffer[0]; // combine consequitive bytes
		do {
			whole_word = whole_word << 8;
			whole_word = whole_word | buffer[c] ;
			c++;
		} while (c != n_width);
		if (DEBUG) printf("current pattern is: 0x%lX\n",whole_word);
		if (whole_word == searched_pattern) {
			stop_byte = (offset_byte + n_width + skip) -1; // magic
			if (DEBUG) printf("found sequence, last byte offset: %lu \n",stop_byte );
			free(buffer);
			n_calls++; // increment n calls
			return (signed long long) stop_byte; // cast to signed
		}
		++offset_byte;		      //
	
	}
	if (n_calls == 2) printf("Not valid zip signature found in the file, exiting...\n"); // detect not valid zip jpg
	else printf("EOF reached \n");
	free(buffer);
	va_end(ap);
	return -2;
}

