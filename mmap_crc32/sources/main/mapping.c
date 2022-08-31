#include "mapping.h"
#include <stdint.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "crc32.h"
#include <inttypes.h>

int test();
void mapping(int fd,size_t filesize);

uint32_t CRC32(uint8_t* data, size_t data_length);

int test(){
    printf("hahahaha\n");
    char* pathname = "testfile";

    struct stat statbuf;
    int fd_fp = 0;
    FILE* fp = NUL;
    if (!(fp = fopen(pathname, "rb")))
    {
        fprintf(stdout, "cannon open %s file, error %d\n", pathname, errno);
        return 0;
    }
    fd_fp = fileno(fp);
    if (!fd_fp) {
        fprintf(stdout, "there were some error while processing %s filename,cannont assign a fd\n", pathname);
	return 0;
    }
    
    int lock = flock(fd_fp, LOCK_SH);
    if (lock)
    {
        fprintf(stdout, "cannot lock fd\n");
    }
    if ((fstat(fd_fp, &statbuf) != 0) || (!S_ISREG(statbuf.st_mode))) {
        fprintf(stdout, "%s file is probably not a regular file \n", pathname);
	return 0;
    }
    size_t filesize = statbuf.st_size;
    printf("mapping filesize %lu \n",filesize);
    if (!filesize) {
	fprintf(stdout,"file %s, filesize is 0\n",pathname);
	return 0;
    }
    printf("fdfd is %d\n",fd_fp);
    mapping(fd_fp,filesize);
    flock(fileno(fp), LOCK_UN);
    if (fclose(fp))
    {
        fprintf(stdout, "error while closing file \n");
    }
    return 1;
}

void mapping(int fd,size_t filesize){
    void* addr_strt = 0;
    size_t len_read = filesize;
    if ( (addr_strt = mmap((void*)0, len_read,PROT_READ, MAP_PRIVATE,fd,0)) == MAP_FAILED) {
	    fprintf(stdout,"error while mapping file %d \n",errno);
    } else {
	    fprintf(stdout,"succesfully opened file for mapping\n");
	    printf("value is 0x%X \n", *((uint8_t*)addr_strt  ));
	    //uint32_t crcval = CRC32((uint8_t*) addr_strt, filesize);
	    //printf("%08" PRIX32  "\n",crcval);
    	    munlock(addr_strt, filesize);
    }
}

uint32_t CRC32(uint8_t* data, size_t data_length) {
	uint32_t crc32 = 0xFFFFFFFFu;
	
	for (size_t i = 0; i < data_length; i++) {
		const uint32_t lookupIndex = (crc32 ^ *(data+i) )& 0xff;
		crc32 = (crc32 >> 8) ^ crc32_table[lookupIndex];  // CRCTable is an array of 256 32-bit constants
	}
	
	// Finalize the CRC-32 value by inverting all the bits
	crc32 ^= 0xFFFFFFFFu;
	return crc32;
}
