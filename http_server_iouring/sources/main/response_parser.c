#include "response_parser.h"

char *extract_bytes(char *str)
{
    char *str_cpy = calloc(sizeof(char), snprintf(0, 0, "%s", str) + 1);
    strcpy(str_cpy, str);
    str_cpy[strlen(str_cpy)] = '\0';
    // char* st_ptr = str;
    char *st_ptr = str_cpy;
    char *part_beg = (void *)0;
    st_ptr = strstr(st_ptr, "GET");
    if (!st_ptr)
    {
        free(str_cpy);
        return (void *)0;
    }
    st_ptr += 4;
    part_beg = st_ptr;
    // printf("|%s \n",st_ptr);
    size_t len = 0;
    if (*(st_ptr + 1) == 32)
    {
        char *ret = calloc(sizeof(char), 2);
        ret[0] = '/';
        ret[1] = '\0';
        if (!ret)
        {
            printf("error while memory allcation\n");
            exit(1);
        }
        free(str_cpy);
        return NULL;
    }
    else
    {
        size_t j = 0;
        while (((*st_ptr) != ' '))
        {
            st_ptr++;
            j++;
        }
        *st_ptr = '\0';
    }
    len = snprintf((void *)0, 0, "%s", part_beg);
    char *ret = calloc(sizeof(char), ++len);
    strncpy(ret, part_beg+1, len-1);
    free(str_cpy);
    return ret;
}
