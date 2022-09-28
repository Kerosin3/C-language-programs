#include "files.h"

int *get_fp_for_files(char **files);

char **get_files_in_dir(char dirname[static 1])
{
    char *to_search = "access";
    DIR *d;
    char absp[PATH_MAX + 1] = {0};
    if (!(realpath(dirname, absp)))
    {
        printf("error opening the dir, aborting\n");
        exit(1);
    }
    struct dirent *dir;
    d = opendir(dirname);
    if (!d)
    {
        printf("error opening the directory, aborting!\n");
        exit(1);
    }
    char **files = malloc((sizeof(char *)));
    char buf[PATH_MAX + 1] = {0};
    size_t j = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)

        {
            if (strstr(dir->d_name, to_search) != NULL)
            {
                size_t len = snprintf(0, 0, "%s/%s", absp, dir->d_name);
                snprintf(buf, len + 1, "%s/%s", absp, dir->d_name); // plus one?
                                                                    // printf("filename is %s\n",buf);
                char *filename = calloc(sizeof(char), len + 1);
                strcpy(filename, buf);
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
        // FILE *some_file = fopen(files[j], "rb");
        int fd_t = open(files[j], O_DIRECT | O_SYNC | O_RDONLY);
        //	int fd_t = open(files[j],O_RDONLY);
        if (fd_t <= 0)
        {
            printf("error while opening %s file,err = %d aborting..\n", files[j], errno);
        }
        files_FD[j] = fd_t;
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
/*
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
*/
