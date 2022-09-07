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
#define NUL (void*)0


int main(){

//	test();
    FILE* fp;
    FILE* fp2;
    FILE* fp3;
    fp = fopen("test2.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }
    fp2 = fopen("test3.txt", "r");
    fp3 = fopen("test4.txt", "r");
    test3(fp,fp2,fp3);

    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    get_files_in_dir();
	return 0;
	
}
