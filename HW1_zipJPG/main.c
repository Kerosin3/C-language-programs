#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JPG_START 0xFFD8
#define JPG_END   0xFFD9

int find_valid_jpg(FILE* fp);

int main(int argc, char *argv[])
{
	signed n_end_jpg = 0;
	if (argc <= 1) {
		printf("Please enter filename, aborting..\n");
		return 0;
	}
	FILE* fp; // all is ok
	//open file
	if ( (fp = fopen(argv[1],"r")) == "NULL" ) {
		printf("error while opening the file, aborting..\n");
		exit(1);
	}
	fp = fopen(argv[1],"rb");
	// end open
	//
	n_end_jpg = find_valid_jpg(fp);
	if (n_end_jpg) {
		printf("xxxxx %d\n",n_end_jpg );
	} else {
		printf("not valid jpg has been found, aborting..\n");
		exit(1);
	}
	
	fclose(fp);
	return 0;
}


int find_valid_jpg(FILE* fp){
	long unsigned int i = 0;
	size_t one_byte = 1;
	size_t flag_st = 0;
	size_t flag_stop = 0;
	unsigned char buff[2]; // buf for word
	unsigned short word = 0xFFFF; //2 bytes

	rewind(fp); //start from the start...
	if (fseek( fp, 0,SEEK_SET )) { // setting beginning of file
		printf(" error setting file! \n");
		exit(1);
		return 0;
	}
	do { // opening....
		fseek(fp,i,SEEK_SET); // shift back one byte
		if (! fread(buff,one_byte,2,fp)) { // not succesfull read
			exit(1);
		}
		//printf("0x%X \n",buff[0]);
		//printf("0x%X \n",buff[1]);
		word = word=((0xFFFF & (buff[0] << 8  )) + buff[1] );
		printf("0x%X\t\t,i = %d \n",word,i);
		if (word == JPG_START) {
			printf("found valid beginning\n");
			flag_st = 1;
		}
		if (word == JPG_END) { // found valid EOI section
			printf("found valid ending\n");
			if (flag_st) return i; // start is also found
		}
		if (feof(fp)) {
			flag_stop = 1;
		}
		++i;
	} while (!flag_stop); 
	printf("end of file reached\n");
	return 0;	// if end of file
		    //
}
