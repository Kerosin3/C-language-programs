#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"


typedef struct MemoryStruct {
	char *memory;
	size_t size;
} MemoryStruct;

static size_t WriteMemoryCallback(void *,size_t,size_t,void*);
static unsigned ParseThisResponse(size_t len, char response[static 1]);
// ??static size_t;

int main(int argc, char *argv[])
{
	CURL* curl;	
	CURLcode response;//response

	MemoryStruct chunk;
	chunk.memory = malloc(1);
	chunk.size = 0;
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl,CURLOPT_URL,"https://wttr.in/Moscow?format=j1");
	
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteMemoryCallback);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*) &chunk);
	curl_easy_setopt(curl,CURLOPT_USERAGENT,"libcurl-agent/1.0");

	response = curl_easy_perform(curl); // get response

/* check for errors */
  	if(response != CURLE_OK) {
	    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(response));
  	}
	  else {
	    printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
	}
	ParseThisResponse(chunk.size,chunk.memory);
	//fprintf(stdout,"%s \n",chunk.memory);
	curl_easy_cleanup(curl);
	free(chunk.memory);
	curl_global_cleanup();
	return 0;

}


static size_t WriteMemoryCallback(void *contents,size_t size,size_t nmemb,void *user_response){
	size_t realsize = size * nmemb;
	MemoryStruct *mem = (MemoryStruct *) user_response;

	char *ptr = realloc(mem->memory, mem->size + realsize +1);
	if (!ptr){
		printf("error while allocating memory, exiting..\n");
		return 0;
	}
	mem -> memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents,realsize);
	mem->size+=realsize;
	mem->memory[mem->size] = 0;
	return realsize;
}

static unsigned ParseThisResponse(size_t len,char response[static 1]){
	if (!len){
		return 0;
	} 
	cJSON *json = cJSON_ParseWithLength(response,len);
	char *parse_out = cJSON_Print(json);
	fprintf(stdout,"your result is %s \n",parse_out);
	cJSON *conditions = (void*)0;
	cJSON *a_condition = (void*)0;
	conditions = cJSON_GetObjectItemCaseSensitive(json,"current_condition");
	a_condition = cJSON_GetObjectItemCaseSensitive(conditions,"FeelsLikeC");
	if (cJSON_IsInvalid(a_condition)){
		printf("wrong data \n");
	}
	if (cJSON_StringIsConst(a_condition)){
		printf("asdasd\n");
		//printf("---->%f\n",a_condition->valueint);

	} else {
		printf("something wrong \n");
	}
	cJSON_Delete(json);
	//cJSON_Delete(conditions);
	//cJSON_Delete(a_condition);
	return 1;

}
