#ifndef FILES
#define FILES

#define _GNU_SOURCE
#include "khash.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

char **get_files_in_dir(char dir[static 1]);
void destroy_filenames(char **files);
void close_all_fd(int *fds);
int *get_fp_for_files(char **files);

#endif
