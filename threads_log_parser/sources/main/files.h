#ifndef FILES
#define FILES

#define _GNU_SOURCE

#include <fcntl.h>
#include <dirent.h> 
#include <stdio.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <limits.h>
#include <errno.h>


char** get_files_in_dir(char dir[static 1]);
void destroy_filenames(char** files);
void close_all_fd(int* fds);
int* get_fp_for_files(char** files);

#endif
