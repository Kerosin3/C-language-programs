#include "bufandfiles.h"
#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * setup buffers
 */

char *buffers;
size_t *buffer_lengths;
int *file_fds;
char **files_in_dir;
char *filesinthedir;

void setup_buffers(int connections)
{
    buffers = malloc(connections * BUFFER_SIZE);
    if (!buffers)
        die("malloc");

    buffer_lengths = malloc(connections * sizeof(size_t));
    if (!buffer_lengths)
        die("malloc");

    file_fds = malloc(connections * sizeof(int));
    if (!file_fds)
        die("malloc");

    files_in_dir = calloc(MAXFILESINTHEDIR, sizeof(char *));
    for (size_t i = 0; i < MAXFILESINTHEDIR; i++)
    {
        files_in_dir[i] = calloc(MAXNAMLEN, sizeof(char));
    }
    if (!files_in_dir)
        die("malloc");

    filesinthedir = calloc(PATH_MAX, sizeof(char));
    if (!filesinthedir)
        die("malloc");
}

void destroy_buffers(char *buffers, size_t *buffer_lengths, int *file_fds, char **fdr)
{
    free(buffers);
    free(buffer_lengths);
    free(file_fds);
    for (size_t i = 0; i < 100; i++)
    {
        free(fdr[i]);
    }
    free(files_in_dir);
    free(filesinthedir);
}
void wrap_destroy_buffer()
{
    destroy_buffers(buffers, buffer_lengths, file_fds, files_in_dir);
}

int get_files_in_dir(char *dirname)
{
    DIR *d;
    struct dirent *dir;
    char absp[PATH_MAX + 1] = {0};
    char a_file[PATH_MAX + 1] = {0};
    realpath(dirname, absp);
    if (!(realpath(dirname, absp)))
    {
        printf("error opening the dir, aborting\n");
        exit(1);
    }
    d = opendir(dirname);
    size_t index = 0;
    char *offset = filesinthedir;
    if (!d)
    {
        printf("error opening the directory, aborting!\n");
        exit(1);
    }
    while ((dir = readdir(d)) != NULL)
    {
        size_t len = snprintf(0, 0, "%s", dir->d_name);
        snprintf(a_file, len + 1, "%s", dir->d_name); //

        memcpy(files_in_dir[index], a_file, len + 1);

        len = snprintf(0, 0, "%s<br>", dir->d_name);
        snprintf(a_file, len + 1, "%s<br>", dir->d_name); //
        memcpy(offset, a_file, len + 1);

        index++;
        offset += len;
    }
    return 1;
}
