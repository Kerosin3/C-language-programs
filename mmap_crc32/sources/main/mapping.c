#include "mapping.h"
#include "crc32.h"
static int mapping(int fd, size_t filesize);

uint32_t crc32_calc(uint8_t *p, uint64_t bytelength);

int calc_hashcrc32(char *pathname)
{
    struct stat statbuf;
    int fd_fp = 0;
    FILE *fp = NUL;
    if (!(fp = fopen(pathname, "rb")))
    {
        fprintf(stdout, "cannon open %s file, error № %d\n", pathname, errno);
        return 0;
    }
    fd_fp = fileno(fp);
    if (!fd_fp)
    {
        fprintf(stdout, "there were some error while processing %s filename,cannot assign a fd\n", pathname);
        return 0;
    }

    int lock = flock(fd_fp, LOCK_SH);
    if (lock)
    {
        fprintf(stdout, "cannot lock fd\n");
        return 0;
    }
    if ((fstat(fd_fp, &statbuf) != 0) || (!S_ISREG(statbuf.st_mode)))
    {
        fprintf(stdout, "%s file is probably not a regular file \n", pathname);
        return 0;
    }
    size_t filesize = statbuf.st_size;
    if (!filesize)
    {
        fprintf(stdout, "file %s, filesize is 0! empty file! \n", pathname);
        return 0;
    }
    if (!mapping(fd_fp, filesize))
    {
        fprintf(stdout, "error while filemapping, aborting..\n");
    }
    flock(fileno(fp), LOCK_UN);
    if (fclose(fp))
    {
        fprintf(stdout, "error while closing file \n");
        return 0;
    }
    return 1;
}

static int mapping(int fd, size_t filesize)
{
    struct rusage usage_cur;
    getrusage(RUSAGE_SELF, &usage_cur);
    void *addr_strt = 0;
    size_t len_read = filesize;
    if ((addr_strt = mmap((void *)0, len_read, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    {
        return 0;
    }
    else
    {
        printf("calced hash value is >>0x%X<<, processed file size is %lu bytes \n",
               crc32_calc((uint8_t *)addr_strt, filesize), filesize);
        printf("used system time:%ld us \n", usage_cur.ru_stime.tv_usec);
        printf("used user time:%ld us \n", usage_cur.ru_utime.tv_usec);
        munlock(addr_strt, filesize);
    }
    return 1;
}

uint32_t crc32_calc(uint8_t *p, uint64_t bytelength)
{
    register uint32_t crc = 0xffffffff;
    while (bytelength-- != 0)
    {
        crc = crc32Table[((uint8_t)crc ^ *(p++))] ^ (crc >> 8);
    }
    return (crc ^ 0xffffffff);
}
