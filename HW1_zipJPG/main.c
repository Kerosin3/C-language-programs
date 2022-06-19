#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JPG_START 0xFFD8
#define JPG_END   0xFFD9
#define DEBUG 	  1
int find_valid_jpg(FILE* fp);

int main(int argc, char *argv[])
{
	unsigned char end_of_fine = 0;
	unsigned n_end_jpg = 0;
	if (argc <= 1) {
		printf("Please enter filename, aborting..\n");
		return 0;
	}
	FILE* fp; // all is ok
	//open file
	if ( (fp = fopen(argv[1],"rb")) == "NULL" ) {
		printf("error while opening the file, aborting..\n");
		exit(1);
	}
	fp = fopen(argv[1],"rb");
	// end open
	//
	if (n_end_jpg = find_valid_jpg(fp)) {
		fseek(fp,1,0); // set cursor to end of jpg section
		fread(&end_of_fine,1,1,fp);
		printf("--------------------------0x%x\n",end_of_fine);
	} else {
		printf("not valid jpg has been found, aborting..\n");
		exit(1);
	}
	
	fclose(fp);
	return 0;
}


int find_valid_jpg(FILE* fp){
	long unsigned int i = 0;
	long unsigned int addr = 0x0;
	size_t one_byte = 1;
	size_t flag_st = 0;
	size_t flag_stop = 0;
	unsigned char buff[2] = {0}; // buf for word
	unsigned short word = 0x0000; //2 bytes
	unsigned short start = 0x0000; //2 bytes
	rewind(fp); //start from the start...
	if (fseek( fp, 0,SEEK_SET )) { // setting beginning of file
		printf(" error setting file! \n");
		exit(1);
		return 0;
	}
	do { // opening....
		if (! fread(&buff[0],one_byte,1,fp)) { // not succesfull read
			if (i % 2)  { // if end of file is not even
				fseek(fp,-2,SEEK_CUR); // set cursor to end of file pre
				fread(&buff[0],one_byte,1,fp); // real pre last
				word = ((0xFFFF & (buff[0] << 8  )) + buff[1] );
				i--;
				if (DEBUG) printf("i=% 6i, word = 0x%04X,\t page=0x%x \t offset = 0x%x \n",i,word,addr,(i) % 16);
			} else  {
				;
			}// if not full word
		}
		//printf("cur tick = 0x%X\t\t,i = %X \n",buff[0],i % 16);
		if (word == JPG_START) {
			flag_st = 1;
			start = i - 1; //previous i
			printf("found valid jpg beginning %u \n",start);
			word = ((0xFFFF & (buff[1] << 8  )) + buff[0] );
		}
		if (word == JPG_END) { // found valid EOI section
			printf("found valid jpg ending\n");
			if (flag_st) return i; // start is also found
		}
		if (feof(fp)) {
			printf("end of file found \n");
			flag_stop = 1;
		}
		if  ((! ( (i) % 16)) & (i != 0)) addr+=0x10; // current mem page
		if (i % 2) {
			word = ((0xFFFF & (buff[1] << 8  )) + buff[0] );
			if (DEBUG) printf("i=% 6i, word = 0x%04X,\t page=0x%x \t offset = 0x%x \n",i,word,addr,i % 16);
		}
		++i;
		buff[1] = buff[0];
	} while (!flag_stop); 
	printf("end of file reached, something gone wrong\n");
	return 0;	// if end of file
		    //
}
