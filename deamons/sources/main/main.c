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
	
    FILE* fp = fopen("test.jzon", "rb");
    assert(fp);
    fseek(fp, 0, SEEK_END);
    size_t filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* data = (char*)malloc(filesize);
    assert(data);
    fread(data, 1, filesize, fp);
    data[filesize] = 0;
    fclose(fp);

    JzonParseResult result = jzon_parse(data);
    JzonValue* mystery_words = jzon_get(&result.output, "mysterious_words_by_id");
    assert(mystery_words->is_table);
    assert(strcmp(jzon_get(mystery_words, "7b09c1a7-01bf-45c0-be19-753e1faecdde")->string_val, "hello") == 0);

    printf("%s \n",jzon_get(mystery_words, "7b09c1a7-01bf-45c0-be19-753e1faecdde")->string_val );
    free(data);

	return 0;
}


