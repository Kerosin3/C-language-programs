#ifndef FILES
#define FILES


#include <dirent.h> 
#include <stdio.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

char** get_files_in_dir();
void destroy_filenames(char** files);
void close_all_fd(int* fds);
int* get_fp_for_files(char** files);

#endif