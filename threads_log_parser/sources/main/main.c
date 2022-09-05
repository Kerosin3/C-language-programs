#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "signal.h"
#include <string.h>

#include "misc.h"

#define NUL (void*)0
#define MAX_LEN 200


int main(){

	test();
/*    FILE* fp;
    fp = fopen("test.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }
    parse_string(fp );

    fclose(fp);
*/	
	return 0;
	
}
