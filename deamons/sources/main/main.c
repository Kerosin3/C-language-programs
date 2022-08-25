#include <stdio.h>
#include <stdlib.h>
#include "deamonize.h"
#include "jzon.h"
#include <assert.h>
#include <string.h>

#define NUL (void*)0


int main(){
//	char *deamon_name = "some_test_deamon";
//	deamonize(deamon_name);
	
    FILE* fp = NUL;
    if (!(fp = fopen("settings.jzon", "rb"))) {
	    fprintf(stderr,"cannon open config file,aborting\n");
	    exit(5);
    }
    fseek(fp, 0, SEEK_END);
    size_t filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* data = malloc(filesize);
    if (!data) {
	    fprintf(stderr,"error while memory allocation \n" );
	    exit(4);
    }
    fread(data, 1, filesize, fp);
    data[filesize] = 0;
    fclose(fp);

    JzonParseResult result = jzon_parse(data);
    if(!result.ok) {
	    fprintf(stderr,"cannot parse settings file\n" );
	    exit(3);
    }
    JzonValue* nested_table_val = jzon_get(&result.output, "daemon_settings");
    assert(nested_table_val->is_table);
    JzonValue* things_arr = jzon_get(nested_table_val, "files_to_watch");
    assert(things_arr->is_array);
    char *valt = jzon_get(things_arr->array_val + 0,"val")-> string_val;
    assert(strncmp(valt, "path1",30) == 0);
    printf("%s\n",valt);
    free(data);

	return 0;
}


