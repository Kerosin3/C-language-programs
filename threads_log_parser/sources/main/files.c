#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *get_fp_for_files(char **files);

char **get_files_in_dir(char dirname[static 1])
{
    char *to_search = "access";
    DIR *d;
    struct dirent *dir;
    d = opendir(dirname);
    if (!d)
    {
        printf("error opening the directory, aborting!\n");
        exit(1);
    }
    char **files = malloc((sizeof(char *)));
    size_t j = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strstr(dir->d_name, to_search) != NULL)
            {
                size_t len = snprintf(0, 0, "%s", dir->d_name);
                char *filename = calloc(sizeof(char), len + 1);
                strcpy(filename, dir->d_name);
                filename[len] = '\0';
                files[j] = filename;
                j++;
                files = realloc(files, sizeof(char *) * (j + 1));
                files[j] = 0;
            }
        }
        closedir(d);
    }
    if (!j)
    {
        printf("no log files found!\n");
        exit(0);
    }
    return files;
}

void destroy_filenames(char **files)
{
    size_t i = 0;
    while ((files[i]))
    {
        free(files[i]);
        i++;
    }
    free(files);
}

int *get_fp_for_files(char **files)
{
    size_t n_files = 0;
    size_t k = 0;
    while ((files[k]))
    {
        n_files++;
        printf("analysing file:%s\n", files[k]);
        k++;
    }
    // printf("n files is %lu\n",n_files);
    int *files_FD = malloc((n_files + 1) * sizeof(int));
    for (size_t j = 0; j < n_files; j++)
    {
        FILE *some_file = fopen(files[j], "rb");
        setbuf(some_file, _IOFBF);
        if (!some_file)
        {
            printf("error while opening %s file, aborting..\n", files[j]);
        }
        files_FD[j] = fileno(some_file);
        int lock = flock(files_FD[j], LOCK_EX);
        if (lock)
        {
            printf("error while locking file %s \n", files[j]);
            exit(1);
        }
        // printf("fd if %d\n",files_FD[j]);
    }
    files_FD[n_files] = -1;
    destroy_filenames(files);
    return files_FD;
}

void close_all_fd(int *fdx)
{
    size_t i = 0;
    while ((fdx[i] != -1))
    {
        if ((flock(fdx[i], LOCK_UN)) == -1)
            printf("error unlocking fd %d\n", fdx[i]);
        if ((fclose(fdopen(fdx[i], "rb"))))
            printf("error while closing fd %d\n", fdx[i]);
        printf("closing %d fd [OK]\n", fdx[i]);
        i++;
    }
    free(fdx);
}
