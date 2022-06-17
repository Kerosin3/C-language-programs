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
	long unsigned int addr = 0;
	size_t one_byte = 1;
	size_t flag_st = 0;
	size_t flag_stop = 0;
	unsigned char buff[2] = {0}; // buf for word
	unsigned short word = 0x0000; //2 bytes
	rewind(fp); //start from the start...
	if (fseek( fp, 0,SEEK_SET )) { // setting beginning of file
		printf(" error setting file! \n");
		exit(1);
		return 0;
	}
	do { // opening....
		if (! fread(&buff[0],one_byte,1,fp)) { // not succesfull read
			exit(1);
		}
		//printf("0x%X \n",buff[0]);
		//printf("0x%X \n",buff[1]);
		printf("result = 0x%X\t\t,i = %d \n",buff[0],i);
		if (word == JPG_START) {
			printf("found valid beginning\n");
			flag_st = 1;
			word = ((0xFFFF & (buff[1] << 8  )) + buff[0] );
		}
		if (word == JPG_END) { // found valid EOI section
			printf("found valid ending\n");
			if (flag_st) return i; // start is also found
		}
		if (feof(fp)) {
			flag_stop = 1;
		}
		if (i % 2) {
			word = ((0xFFFF & (buff[1] << 8  )) + buff[0] );
			printf("i= %i, word = 0x%X, addr=0x%x \n",i,word,i*(i%15));
		}
		++i;
		buff[1] = buff[0];
	} while (!flag_stop); 
	printf("end of file reached\n");
	return 0;	// if end of file
		    //
}
