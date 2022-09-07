#include "files.h"
#include <stdlib.h>
#include <string.h>

void get_files_in_dir(){
  char* to_search = "test";
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  char** files = malloc((sizeof(char*)));
  size_t j = 0;
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
      if (strstr(d_name, to_search) != NULL) {
    		strcpy(files[j],dir->d_name); 	
	}
    }
    closedir(d);
  }
}

