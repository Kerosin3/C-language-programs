#include "hash_f.h"
#define IS_UNSIGNED(t) ((t)~1 > 0)

unsigned long table_size = 10;
unsigned long long calc_hash(char* input_string){
	//printf("hash - %s \n",(char*) input_string);
	if ((sizeof(uint8_t) != (sizeof(char))) ) {
		printf("platform error!,aborting...\n");
		return 0;
	}
	char* str_ptr =(char*) input_string; // its ok
	//size_t str_size= strnlen(str_ptr,25); // size of analyzed string dont know max size...
	size_t str_size= strlen(str_ptr); // size of analyzed string
	//char* to_analyze[str_size+1];// assign now string plus null terminator
	//strcpy(to_analyze,str_ptr); // no strncpy...copy string...
	//size_t l_to_analyze = strnlen(str_ptr,25);
	printf("copied string is %s, its length is %d \n",str_ptr,str_size);
	unsigned long long temp_c= 0;
	for (size_t i = 0; i < str_size; ++i) {// not includes null terminator
		temp_c+=( ((uint8_t) str_ptr[i] ) * pow(((unsigned) SALT),i)  ); // unicode is always 7 byte with leading zero
		//printf("value is 0x%X, your hash is %llu\n",(uint8_t) str_ptr[i],temp_c);
	}
	return temp_c;
	
}

record init_a_record(){
	record a_record;
	a_record.id = 0;
	a_record.key = '\0';
	a_record.value = 0;
	return a_record;
}

record_storage init_storage(){
	record_storage storage;
	storage.current_size = 1;
	storage.max_size= 10;
	record** pt_first = calloc(sizeof(record*), 1); // allocate one main pointer
	*pt_first = calloc(sizeof(record), 10);  // allocate space for 10 pointer to 1 record   calloc(sizeof(record)*n,10) -- 10 pointers to 10 record
	if ( !(pt_first) || !(*pt_first) ) {
		printf("error memory allocation, aborting\n");
		exit(1);
	}// WTF???
	storage.start_record = pt_first;
	//storage.start_record = (record*) calloc(1, sizeof(record));
	return storage;
}
void storage_destroy(record_storage* storage ){
	free(*(storage->start_record));
	free((storage->start_record));
}
//create a destructor??..
void set_a_record(record* rec_ptr,char* in_string){
	unsigned str_l = strlen(in_string); // dangerous
	str_l++; //null terminator
	char* ptr = calloc(str_l,sizeof(uint8_t));
	if (!(ptr)){
		printf("cannot allocate memore, aborting\n");
		exit(1);
	}
	strcpy(ptr,in_string);
	rec_ptr->key=ptr;
	rec_ptr->id = calc_hash(ptr); //assign hash
	//printf("has value inside is %llu\n",rec_ptr->id);
	printf("copied string is %s\n",rec_ptr->key);
	printf("lenths are %d %d \n",strlen(in_string),strlen(rec_ptr->key));
	rec_ptr->value = 1;
}

unsigned try_append_to_storage(record_storage* storage,record a_record){
	if ((storage->current_size) >= (storage->max_size)){
		printf("expanding the table by 10 entries!!!!!!!\n");
		record* pt_old = * (storage->start_record); // store old ptr
		record* pt_new = calloc(sizeof(record),(storage->max_size)+10 ) ;  // add 10 records
		if (!(pt_new)){
			printf("error memory allocation, abouring..\n");
			exit(1);
		}
		unsigned prev_size = storage->max_size; // store old
		storage->max_size+=10; // add value
		memcpy(pt_new,pt_old,sizeof(record)*prev_size);
		storage->start_record = &pt_new;  //assign new
		free(&pt_old); //free old
	}	
	unsigned long tposition =   (a_record.id) % ( (storage->max_size) -1 ); // calc position in the table
	unsigned long cur_position = tposition;
	printf("lenths------- are %d \n",strlen(a_record.key));
//	printf("lenths----tttt--- are %d \n",strlen(   (*((*(storage->start_record)+cur_position))   ).key   ));
	if (!(check_position(storage,a_record,tposition))) { // not equal
		printf("add new value \n");
		*((*(storage->start_record)+cur_position)) = a_record; // copy value
		printf("lenths----xxx--- are %d \n",strlen(   (*((*(storage->start_record)+cur_position))   ).key   ));
	}
	else{ // equal
	        printf("occur is storagexxxxxxxxxxxxxxxxxx: %ld\n",(*(*(storage->start_record)+tposition)).value  );
		((*(*(storage->start_record)+tposition)).value)++;// add value
	}
	printf("going to copy %s\n",a_record.key);
	//unsigned cur_position = (storage->current_size) -1 ; //starting from 0 /// simple increment postition
	printf("position is %d, inside: %s, position in table: %u, occur: %lu \n",cur_position,((record)  *((*(storage->start_record)+cur_position))).key,tposition, ((*(*(storage->start_record)+cur_position)).value)) ;
	printf("lenths in store after append %d \n",strlen(   (*((*(storage->start_record)+cur_position))   ).key   ));
	storage->current_size++;
}
//record get_a_record(char* check_this_input){
unsigned check_position(record_storage* storage,record a_record,unsigned long try_this_position){ // whether it is already occupied
	const char* string_on_this_position =  (*((*(storage->start_record)+try_this_position))).key ;
	const char* string_to_check =  a_record.key;
	printf("--------------------------%s\n",string_on_this_position);
	printf("--------------------------%s\n",string_to_check);
	//char* t0 = "haha";
	//char* t1 = "haha";
	//int rez = (strcmp(t0,t1));
	printf("len 0 is %d, len 1 is %d \n",strlen(&string_on_this_position),strlen(string_to_check));
	int rez = (strcmp(&string_on_this_position,&string_to_check));
	printf("result is %d \n",rez);
	if (rez){ // not equal,
		return 0; // go and write	
	} else { //if collision, match
		return 1; //ooccupied 
	}
}
//unsigned set_serial()
	
//}

void test0(){
	record_storage store = init_storage();
	{
		char const*const some[3] = {
			"englh",
			"fransis",
			"fransis",
		};
	printf("hhhhhhhhhhh %s\n",some[2]);
	for (size_t i = 0; i < 3; ++i) {
		record tmp_rec = init_a_record();
		set_a_record(&tmp_rec,some[i]);
		try_append_to_storage(&store,tmp_rec);
	}
	//record t0 = init_a_record();
	//char* str= "english";
	/*
	set_a_record(&t0,str);
	record t1 = init_a_record();
	char* str1= "text.";
	set_a_record(&t1,str1);

	printf("check is %s \n",t0.key);
	printf("check is %s \n",t1.key);
	**(store.start_record) = t0; 
	try_append_to_storage(&store,t0);
	try_append_to_storage(&store,t0);
	try_append_to_storage(&store,t1);
	**(store.start_record) = t0; 
	store.start_record[0][1] = t0; //copy!!!!
	*(*(store.start_record)+1) = t1;
	store.start_record[0][2] = t1;
	*/
	}


	printf("what is that?? %s\n", (*(*(store.start_record)+5 )).key) ;
	printf("what is that?? %d\n", (*(*(store.start_record)+5 )).value) ;
	printf("what is that?? %d\n", (*(*(store.start_record)+5 )).id) ;
	printf("what is that?? %s\n", (*(*(store.start_record)+2 )).key) ;
	printf("what is that?? %d\n", (*(*(store.start_record)+2 )).value) ;
	printf("what is that?? %d\n", (*(*(store.start_record)+2 )).id) ;
	//printf("what is that?? %s\n", (*(*(store.start_record)+2 )).key) ;

	//printf("what is that?? %s\n",((record) *(*(store.start_record)+1  )).value  );
	//printf("what is that?? %llu \n",(store.start_record[0])->id);
	//printf("what is that?? %llu \n",(store.start_record[0])->value);
	//printf("what is that?? %llu \n",(store.start_record++)->value);
	//printf("what is that?? %s\n",(char*) (store.start_record[1][0]).key);
	//printf("what is that?? %llu \n",(store.start_record[1][0]).id);
	//printf("what is that?? %u \n",(store.start_record[1][0]).value);

	storage_destroy(&store);
}
/*unsigned append_a_record_to_storage(record_storage* storage,record input_record){
	storage->

}*/
