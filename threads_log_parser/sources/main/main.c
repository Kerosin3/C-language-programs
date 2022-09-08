#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "signal.h"
#include <string.h>

#include "misc.h"
#include "test.h"
#include "files.h"
#include "thrd_store.h"
#define NUL (void*)0


int main(){

//	test();
//

    FILE* fp;
    FILE* fp2;
    FILE* fp3;
    fp = fopen("access0.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }
    fp2 = fopen("access1.txt", "r");
    fp3 = fopen("access2.txt", "r");
    test3(fileno(fp),fileno(fp2),fileno(fp3));

    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    /*
    char** files = get_files_in_dir();
    int* fdx = get_fp_for_files(files);
    process_data(fdx);*/
    return 0;
	
}
