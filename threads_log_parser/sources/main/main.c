#include "files.h"
#include "khash.h"
#include "khash_setup.h"
#include "misc.h"
#include "signal.h"
#include "test.h"
#include "thrd_store.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <threads.h>
#include <unistd.h>
#define NUL (void *)0

int main(int argc, char *argv[])
{
    if ((argc > 2 || (argc == 1)))
    {
        printf("please specify just a directory, exiting..\n");
        exit(1);
    }

    char **files = get_files_in_dir(argv[1]);
    int *fdx = get_fp_for_files(files);
    process_data(fdx);
    free(fdx);
    return 0;
}
