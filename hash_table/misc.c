#include "misc.h"

extern void printout_content(record_storage* storage){
	record* t_rec = *(storage->start_record); // add index here
	size_t i = 0;
	size_t j = 0;
	printf("====================================================\n");
	while(i < storage->max_size){
		if (t_rec->flag) { //no empty
			printf("%lu item:%s, occur:%lu \n",j,t_rec->key,t_rec->value);
			j++;
		} else {
			;
		}
		t_rec++;
		i++;
	}
	printf("====================================================\n");
}
