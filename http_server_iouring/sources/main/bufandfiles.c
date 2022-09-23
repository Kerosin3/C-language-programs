#include "bufandfiles.h"
/*
 * setup buffers
 */

char *buffers;
size_t *buffer_lengths;
int *file_fds;
char **fds_to_send;

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

    fds_to_send = calloc(100, sizeof(char*) );
    for (size_t i = 0; i< 100; i++) {
    	fds_to_send[i] = calloc(MAXNAMLEN,sizeof(char));
    }
    if (!fds_to_send)
        die("malloc");
}

int get_files_in_dir(char *dirname)
{
    DIR *d;
    struct dirent *dir;
    char absp[PATH_MAX + 1] = {0};
    char a_file[PATH_MAX + 1] = {0};
    realpath(dirname, absp);
    d = opendir(dirname);
    size_t index = 0;
    if (!d)
    {
        printf("error opening the directory, aborting!\n");
        exit(1);
    }
    while ((dir = readdir(d)) != NULL)
    {
    printf("hahah\n");
        //size_t len = snprintf(0, 0, "%s/%s", absp, dir->d_name);
        //snprintf(a_file, len + 1, "%s/%s", absp, dir->d_name); //
	size_t len = snprintf(0, 0, "%s", dir->d_name);
        snprintf(a_file, len + 1, "%s",  dir->d_name); //

        puts(a_file);
	memcpy(fds_to_send[index],a_file,len+1);
        index++;
    }
    return 1;
}

void close_fd_to_send(int *base)
{
    for (size_t i = 0; i < 1000; i++)
    {
//         close(fds_to_send[i]);
    }
}
