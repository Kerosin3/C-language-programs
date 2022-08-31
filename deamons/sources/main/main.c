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
    
    bool denable = false;
    denable = if_deamon();
    if (denable)
    {
        printf("starting the deamon...\n");
    	openlog("filesize tracker deamon", LOG_CONS | LOG_PID, LOG_DAEMON);
        deamonize(DEAMON_SETUP);
    }
    else
    {
    	openlog("filesize tracker", LOG_CONS | LOG_PID, LOG_DAEMON);
	start_server(APP_SETUP);
    }
    return 0;
}
