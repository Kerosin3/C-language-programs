#include "cJSON.h"
#include <assert.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_lookups 3
#define CITY_NAME_MAX 25
//#define DEBUG
//#define NDEBUG
typedef struct MemoryStruct
{
    char *memory;
    size_t size;
} MemoryStruct;

static size_t WriteMemoryCallback(void *, size_t, size_t, void *);
static unsigned ParseThisResponse(size_t len, char response[static 1],const char* cityname);
static const char *RequestString(char city_name[static 1]);

int main(int argc, char *argv[])
{

    if (argc > 2 || (argc == 1))
    {
        printf("please specify just an exising city name (25 char limit), terminating the program...\n");
        exit(1);
    }
    assert(strnlen(argv[1], CITY_NAME_MAX) != 0 && "error, please enter valid cityname");
    assert(strnlen(argv[1], CITY_NAME_MAX) <= CITY_NAME_MAX && "error, max city name length is 25 chars");

    const char *cityname = RequestString(argv[1]);
    CURL *curl;
    CURLcode response; // response

    MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, cityname);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    response = curl_easy_perform(curl); // get response

    /* check for errors */
    if (response != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\nPlease check you internet connction and request format\n", curl_easy_strerror(response));
        goto end_main;
    }
    else
    {
#ifdef DEBUG
        printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
#endif
    }
    if (ParseThisResponse(chunk.size, chunk.memory,argv[1]))
    {
        fprintf(stderr, "There were some errors while getting the information\nPlease, check the entered data\n");
    }
end_main:
    curl_easy_cleanup(curl);
    free(chunk.memory);
    curl_global_cleanup();
    free((char *)cityname);
    return 0;
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *user_response)
{
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)user_response;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr)
    {
        printf("error while allocating memory, exiting..\n");
        return 0;
    }
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

static unsigned ParseThisResponse(size_t len, char response[static 1],const char *acityname)
{
    char const *const lookup[n_lookups] = {
        // parameters
        "temp_C",
        "winddir16Point",
        "windspeedKmph",
    };
    size_t flag_wr = 0;
    unsigned status = 1;
    if (!len)
    {
        return 1;
    }
    cJSON *json = cJSON_ParseWithLength(response, len);
    if (!json)
    {
        const char *errror_ptr = cJSON_GetErrorPtr();
        if (!errror_ptr)
            fprintf(stderr, "Error while getting json %s \n", errror_ptr);
        status = 1;
        goto end;
    }
#ifdef DEBUG
    char *parse_out = cJSON_Print(json); // parse response
    fprintf(stdout, "your result is %s \n", parse_out);
#endif
    //--read region
    unsigned flag_reg = 0;
    cJSON *region_field = cJSON_GetObjectItemCaseSensitive(json, "nearest_area");
    if (!region_field || cJSON_IsInvalid(region_field))
    {
        fprintf(stderr, "error while parsing region\n");
        status = 1;
        goto end;
    }
    cJSON *a_field = (void *)0;
    cJSON_ArrayForEach(a_field, region_field)
    {
        cJSON *region_info = cJSON_GetObjectItemCaseSensitive(a_field, "region");
	if (cJSON_IsInvalid(region_info)){
            fprintf(stderr, "error getting region info\n");
	    status = 1;
	    goto end;
	}
        if (!flag_reg)
        {
            flag_reg = 1;
            cJSON *reg_name = (void *)0;
            cJSON_ArrayForEach(reg_name, region_info)
            {
                reg_name = cJSON_GetObjectItemCaseSensitive(reg_name, "value");
                if (cJSON_IsString(reg_name))
                {
		    if (!strstr(reg_name->valuestring,acityname)) {
			status = 1;
		    	goto end;
		    }
    		    fprintf(stdout, "searching weather conditions for city >> %s << \n", reg_name->valuestring);
                }
                else
                {
                    fprintf(stderr, "error while reading region\n");
                    status = 0;
                    goto end;
                }
            }
        }
    }
    cJSON *conditions = (void *)0;
    conditions = cJSON_GetObjectItemCaseSensitive(json, "current_condition");
    if (!conditions || cJSON_IsInvalid(conditions))
    {
        fprintf(stderr, "error while parsing weather conditions\n");
        status = 1;
        goto end;
    }
    cJSON *a_parameter = (void *)0;
    cJSON_ArrayForEach(a_parameter, conditions)
    {
        for (size_t i = 0; i < n_lookups; ++i)
        {
            cJSON *w_condititon = cJSON_GetObjectItemCaseSensitive(a_parameter, lookup[i]);
            if (cJSON_IsInvalid(w_condititon) || (!(w_condititon->valuestring))){
                fprintf(stderr, "error getting w_condititon\n");
	    	status = 1;
		goto end;
	    }
            switch (i)
            {
            case 0:
                if (cJSON_IsString(w_condititon))
                    fprintf(stdout, "current temperature is %s degress of Celsius\n", w_condititon->valuestring);
                else
                    fprintf(stderr, "error while reading value of temperature\n");
                status = 1;
                break;
            case 1:
                if (cJSON_IsString(w_condititon))
                    fprintf(stdout, "current wind direction is %s\n", w_condititon->valuestring);
                else
                    fprintf(stderr, "error while reading value of wind direction\n");
                status = 1;
                break;
            case 2:
                if (cJSON_IsString(w_condititon))
                    fprintf(stdout, "current wind speed is %s km/h\n", w_condititon->valuestring);
                else
                    fprintf(stderr, "error while reading value of speed of wind\n");
                status = 1;
                break;
            default:
                fprintf(stderr, "something wrong happended,exiting..\n");
                status = 1;
                goto end;
            }
            if (!flag_wr)
            { // weather discription read
                flag_wr = 1;
                cJSON *w_conditions = (void *)0;
                w_conditions = cJSON_GetObjectItemCaseSensitive(a_parameter, "weatherDesc");
                if ((!w_conditions) || cJSON_IsInvalid(w_conditions))
                {
                    fprintf(stderr, "error while getting weather conditions\n");
                    status = 0;
                    goto end;
                }
                cJSON *a_weather = (void *)0;
                cJSON_ArrayForEach(a_weather, w_conditions)
                {
                    cJSON *weather_disc = cJSON_GetObjectItemCaseSensitive(a_weather, "value");
                    if (cJSON_IsString(weather_disc))
                    {
                        fprintf(stdout, "current weather discription is %s \n", weather_disc->valuestring);
                    }
                    else
                    {
                        fprintf(stderr, "error while reading weaher discriptios\n");
                        status = 0;
                        goto end;
                    }
                }
            }
        }
    }
    status = 0; // OK!
end:
    cJSON_Delete(json);
    return status;
}

static const char *RequestString(char city_name[static 1])
{
    const char *beg = "https://wttr.in/";
    size_t total_l = strlen(beg);
    const char *end = "?format=j1";
    total_l += strlen(end);
    total_l += strnlen(city_name, CITY_NAME_MAX);
    char *string_req = calloc(total_l + 1, sizeof(char));
    if (!string_req)
    {
        fprintf(stderr, "error while memory allocation\n");
    }
    strcat(string_req, beg);
    strcat(string_req, city_name);
    strcat(string_req, end);
    string_req[total_l] = '\0';
    return string_req;
}
