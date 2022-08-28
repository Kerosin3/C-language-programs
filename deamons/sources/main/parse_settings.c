#include "parse_settings.h"
#include "jzon.h"
#include <assert.h>


void destroy_paths(char** pathz){
	size_t j = 0;
	while (pathz[j]) {
		free(pathz[j]);
		pathz[j] = NUL;
		j++;
	}
	free(pathz);
}

char** paths_to_analyze(_Bool* denable){
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
    data[filesize] = 0; // WHY?
    if (fclose(fp)) {
	    fprintf(stderr,"error while closing file \n" );
	    exit(4);
    }

    JzonParseResult result = jzon_parse(data);
    free(data);
    if(!result.ok) {
	    fprintf(stderr,"cannot parse settings file\n" );
	    exit(3);
    }
    JzonValue* nested_table_val = jzon_get(&result.output, "daemon_settings");
    assert(nested_table_val->is_table);
    JzonValue* things_arr = jzon_get(nested_table_val, "files_to_watch");
    assert(things_arr->is_array);
    char *valt = jzon_get(things_arr->array_val ,"val")-> string_val;
    size_t jj= 0;
    while ( strncmp(valt,"END_PATH",50)){
	jj++;
	valt = jzon_get(things_arr->array_val + jj,"val")-> string_val;
    }
    char **paths = malloc(sizeof(char*) * (jj) ); // add exter for NULL
    if (!paths){
	    fprintf(stderr,"cannot allocate memory!\n" );
	    exit(4);
    }
    for (size_t t =0; t< jj ; t++) { //END -1
	    char *temp_str = jzon_get(things_arr->array_val + t,"val")-> string_val;
	    size_t size_of_temp_str = strlen(temp_str);
	    size_of_temp_str;
	    paths[t] = malloc(sizeof(char) *(size_of_temp_str+1 ) );
	    if (! (paths[t])) {
	    	fprintf(stderr,"cannot allocate memory!\n" );
	    	exit(4);
	    }
	    strcpy(paths[t], temp_str);
	    paths[t][size_of_temp_str] = '\0';
	    printf("->>%s \n",paths[t]);
    }
    paths[jj]= NUL;
    JzonValue* deamon_enable = jzon_get(&result.output, "enable_deamonization");
    assert(deamon_enable->is_bool);
    *denable = deamon_enable->bool_val;
    return paths;
}
