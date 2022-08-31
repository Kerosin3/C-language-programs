#include "parse_settings.h"
#include <stdbool.h>

void destroy_paths(char **pathz)
{
    size_t j = 0;
    while (pathz[j])
    {
        free(pathz[j]);
        pathz[j] = NUL;
        j++;
    }
    free(pathz[j]);
    pathz[j] = NUL;
    free(pathz);
}

char **paths_to_analyze()
{
    FILE *fp = NUL;
    if (!(fp = fopen("settings.jzon", "rb")))
    {
        syslog(LOG_ERR, "cannon open config file");
        exit(5);
    }
    fseek(fp, 0, SEEK_END);
    size_t filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *data = malloc(sizeof(char) * filesize);
    if (!data)
    {
        syslog(LOG_ERR, "error while memory allocation ");
        exit(4);
    }
    fread(data, 1, filesize, fp);
    if (fclose(fp))
    {
        syslog(LOG_ERR, "error while closing file ");
        exit(4);
    }

    JzonParseResult result = jzon_parse(data);
    if (!result.ok)
    {
        syslog(LOG_ERR, "cannot parse settings file");
        exit(3);
    }
    JzonValue *nested_table_val = jzon_get(&result.output, "daemon_settings");
    assert(nested_table_val->is_table);
    JzonValue *things_arr = jzon_get(nested_table_val, "files_to_watch");
    assert(things_arr->is_array);
    size_t jj = 0;
    size_t size_of_paths = things_arr->size;
    jj = size_of_paths;
    char **paths = malloc(sizeof(char *) * (jj + 1)); // add extra for NULL, main point
    if (!paths)
    {
        syslog(LOG_ERR, "cannot allocate memory!");
        exit(4);
    }
    for (size_t t = 0; t < jj; t++)
    { // END -1
        char *temp_str = jzon_get(things_arr->array_val + t, "val")->string_val;
        size_t size_of_temp_str = strlen(temp_str);
        paths[t] = malloc(sizeof(char) * (size_of_temp_str + 1)); // sub points
        if (!(paths[t]))
        {
            syslog(LOG_ERR, "cannot allocate memory!");
            exit(4);
        }
        strcpy(paths[t], temp_str);
        paths[t][size_of_temp_str] = '\0';
    }
    paths[jj] = NUL;
    jzon_free(&result.output);
    free(data);
    return paths;
}

bool if_deamon()
{
    FILE *fp = NUL;
    if (!(fp = fopen("settings.jzon", "rb")))
    {
        syslog(LOG_ERR, "cannon open config file,aborting");
        exit(5);
    }
    fseek(fp, 0, SEEK_END);
    size_t filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *data = malloc(sizeof(char) * filesize);
    bool ret = false;
    if (!data)
    {
        syslog(LOG_ERR, "error while memory allocation");
        free(data);
        exit(4);
    }
    fread(data, 1, filesize, fp);
    if (fclose(fp))
    {
        syslog(LOG_ERR, "error while closing file");
        free(data);
        exit(4);
    }

    JzonParseResult result = jzon_parse(data);
    if (!result.ok)
    {
        syslog(LOG_ERR, "cannot parse settings file");
        exit(3);
    }
    JzonValue *deamon_enable = jzon_get(&result.output, "enable_deamonization");
    assert(deamon_enable->is_bool);
    ret = deamon_enable->bool_val;
    jzon_free(&result.output);
    free(data);
    return ret;
}
