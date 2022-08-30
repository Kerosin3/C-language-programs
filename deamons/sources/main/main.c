#include "deamon_magic.h"
#include "deamonize.h"
#include "parse_settings.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    
    _Bool denable = false;
    denable = if_deamon();
    if (denable)
    {
        printf("starting the deamon...\n");
    	openlog("filesize tracker deamon", LOG_CONS | LOG_PID, LOG_DAEMON);
        deamonize();
    }
    else
    {
    	openlog("filesize tracker", LOG_CONS | LOG_PID, LOG_DAEMON);
        char **paths = paths_to_analyze();
        size_t j = 0;
        size_t filesize = 0;
        while (paths[j])
        {
            if (!(filesize = calc_filesize(paths[j])))
            {
                fprintf(stdout, "error while processing >>%s<< file, check whether it exists\n", paths[j]);
            }
            else
            {
                fprintf(stdout, "filename is %s, filesize is >>%lu<< bytes\n", paths[j], filesize);
            }
            j++;
        }
        destroy_paths(paths);
    }
    return 0;
}
