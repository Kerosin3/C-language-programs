#include "signal.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <threads.h>
#include "khash_setup.h"
#include "khash.h"
#include "files.h"
#include "misc.h"
#include "test.h"
#include "thrd_store.h"
#define NUL (void *)0

//int khInt = 666;
//KHASH_MAP_INIT_STR(khInt, int);

//extern const int khStrInt;

int main(int argc, char *argv[])
{
    if ((argc > 2 || (argc == 1)))
    {
        printf("please specify just a directory, exiting..\n");
        exit(1);
    }
    file_map = kh_init(filemap_t);
    mtx_init(&mtx_khash_store,mtx_plain);

    char **files = get_files_in_dir(argv[1]);
    int *fdx = get_fp_for_files(files);
    process_data(fdx);
    return 0;
}
