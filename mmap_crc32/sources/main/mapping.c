#include "mapping.h"
#include <sys/mman.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


int test();
void mapping(int fd,size_t filesize);

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
    mapping(fd_fp,filesize);
    flock(fileno(fp), LOCK_UN);
    if (fclose(fp))
    {
        fprintf(stdout, "error while closing file \n");
    }
}

void mapping(int fd,size_t filesize){
    void* addr_strt = 0;
    size_t len_read = 10000;
    if ( mmap(addr_strt, len_read,PROT_READ,MAP_PRIVATE,fd,0) == MAP_FAILED) {
	    fprintf(stdout,"error while mapping file\n");
	    exit(1);
    } else {
	    fprintf(stdout,"succesfully opened file for mapping\n");
    }

    

}
