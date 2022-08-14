#include <stdio.h>
#include "curl.h"

int main(int argc, char *argv[])
{
	CURL* curl;	
	CURLcode response;//response

	curl = curl_easy_init();
	curl_easy_setopt(curl,CURLOPT_URL,"https://yandex.ru");
	

	response = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return 0;
}
