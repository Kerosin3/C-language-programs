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
unsigned long long rehash(unsigned long long in_hash){
	printf("calcing new has value.....\n");
	int str_len = snprintf(NULL,0,"%u",in_hash);// get the size
	str_len++ ;//space for null term
	char* str_converted = malloc(str_len);
	snprintf(str_converted,str_len,"%d",in_hash);
	unsigned long long new_hash = calc_hash(str_converted);
	printf("----------prev hash value %llu---------new hash value is %llu \n",in_hash,new_hash);
	free(str_converted); // free memory
	return new_hash;
}



record init_a_record(){
	record a_record;
	a_record.id = 0;
	a_record.key = '\0';
	a_record.value = 0;
	a_record.flag = not_written;
	return a_record;
}

record_storage init_storage(){
	record_storage storage;
	storage.current_size = 0;
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
	printf("destroying..\n");
	unsigned tp =0;
	for (size_t i = 0; i < storage->max_size; ++i) {
		if (   ((*(*(storage->start_record)+tp)).flag) ) {
			printf("trying to free %d\n",tp);
			free(  ((*(*(storage->start_record)+tp)).key)    );
			tp++;
		}
	}
	//free(*(storage->start_record));
	//*(storage->start_record) = NULL;
	//
	//free((storage->start_record));// ??? OK??
	//storage->start_record = NULL;
	// CHECK WHETHER NOT DOUBLE FREEE
	printf("freed %d objects\n",tp); 
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

signed check_occupy(record_storage* storage,unsigned long position){
	printf("checking.1. postition %d, storage:%p\n",position,storage);
	printf("pointer is %p \n", &((*(*(storage->start_record)+position)).flag  ) );
	enum flag_written flag = (*(*(storage->start_record)+position)).flag; //check whether its writtne
	//enum flag_witten flag =  (*(*(storage->start_record)+position)).flag;
	printf("checking.2..\n");
	if (flag>0) { //written
		return 1;
	} else if (flag==0){
		return 0;
	} else {
		return -1;
	}
	
} 


unsigned try_append_to_storage(record_storage* storage,record a_record){
	if ((storage->current_size) >= (storage->max_size)){
		printf("expanding the table by 10 entries!!!!!!!\n");
		record* pt_old = * (storage->start_record); // store old ptr
		record* pt_new = calloc(sizeof(record),(storage->max_size)+10 ) ;  // add 10 records
		unsigned prev_size = storage->max_size; // store old
		storage->max_size+=10; // add value
		if (!(pt_new) || !(pt_old)){ // check before copy
			printf("error memory allocation, abouring..\n");
			exit(1);
		}
		memcpy(pt_new,pt_old,sizeof(record)*prev_size);
		storage->start_record = &pt_new;  //assign new
		free(pt_old); //free old
		pt_old = NULL;
		enum flag_written flag = (*(*(storage->start_record)+7)).flag; //check whether its writtne
		printf("pointer to 7th after expand is %p \n", &((*(*(storage->start_record)+7)).flag  ) );
		printf("pointer to main pointer %p ,assigned %p\n", storage->start_record,&pt_new);
		printf("we are here! max size now is %d, val=%d\n",storage->max_size,flag);

	}
	unsigned long long new_hash;
	new_hash = 0;
	//unsigned long long *hash_ptr = &record.id;
jump_0:
	unsigned long tposition =   (a_record.id) % ( (storage->max_size)  ); // calc position in the table MUNUS ONE?
	printf("============has value after jump:%llu, position is %u, string %s \n",new_hash,tposition,a_record.key);
	unsigned long cur_position = tposition;
	signed occupied =0;
	printf("element show:%d\n",a_record.flag);
	printf("test, store adress %p \n",storage);
	occupied =check_occupy(storage,cur_position); //check whether position is occupied???
	if (occupied>0){
		if (!(check_position(storage,&a_record,tposition))) { // not equal & occupied!
			printf("collision!!!!\n");			
			new_hash = rehash(a_record.id); // calc new hash value
			a_record.id = new_hash; //assign new hash
			printf("goto->>>>>\n");
			goto jump_0; // go an find a space in table
			//(*((*(storage->start_record)+tposition))).flag = moved; // after all mark as moved
		//	*((*(storage->start_record)+cur_position)) = a_record; // copy value
			//a_record.key[0]='A'; // change value
		
		} else { // equal  and occupied!  -> ADD COUNT!
	        	printf("occur is storagexxxxxxxxxxxxxxxxxx: %ld\n",(*(*(storage->start_record)+tposition)).value  );
			((*(*(storage->start_record)+tposition)).value)++;// add value
		}
	

	} else if (occupied==0) {// if not ocuppied
		printf("add new entry %s \n",a_record.key);
		copy_obj(storage,a_record,cur_position);
		storage->current_size++;
	} else { //moved...
		printf("I AM HERE________________________\n");
	}
	printf("position is %d, inside: %s, position in table: %u, occur: %lu ,written? = %d \n",cur_position,((record)  *((*(storage->start_record)+cur_position))).key,tposition, ((*(*(storage->start_record)+cur_position)).value),   ((*(*(storage->start_record)+cur_position)).flag)  ) ;
	char* test = (*((*(storage->start_record)+cur_position))   ).key;   
	printf("size of table:%d\n",storage->current_size);
	printf("-------------------------------------------\n");
}

void copy_obj(record_storage* storage,record a_record,unsigned long position){
	unsigned s_len = strlen(a_record.key) +1 ; //add null t
	char* s_tmp = calloc(sizeof(char), s_len); //allocate memory for string
	if (!(s_tmp)) {
		printf("error memeory allocation\n");
		exit(1);
	}
	printf("copying string= %s\n", a_record.key);
	strcpy( s_tmp,(a_record.key  ));
	s_tmp[s_len] = '\0';
	printf("copying done, string= %s\n", s_tmp);
	(*((*(storage->start_record)+position))).key = s_tmp;
	(*((*(storage->start_record)+position))).id = a_record.id;
	(*((*(storage->start_record)+position))).value = a_record.value;
	(*((*(storage->start_record)+position))).flag = written;

	//printf("copying done, string= %s\n", (char*) (*((*(storage->start_record)+position))).value  );
	printf("copying done, string= %s\n", s_tmp);
}

//record get_a_record(char* check_this_input){
unsigned check_position(record_storage* storage,record* a_record,unsigned long try_this_position){ // whether it is already occupied
	char* string_on_this_position =  (*((*(storage->start_record)+try_this_position))).key ;
	char* string_to_check =  a_record->key;
//	if (!(string_on_this_position == NULL)) 
	printf("--------------------------%s\n",string_on_this_position);
	printf("--------------------------%s\n",string_to_check);
	int rez = -1;
	if (string_on_this_position != NULL ){
		printf("len 0 is %d, len 1 is %d \n",strlen(string_on_this_position),strlen(string_to_check));
		rez = (strcmp(string_on_this_position,string_to_check));
	} else {
		printf("len of input string is %d \n",strlen(string_to_check));
		rez = 1;
	}
	printf("result of comparision is %d \n",rez);
	if (rez){ // not equal,
		return 0; // go and write	
	} else { //if collision, match
		return 1; //ooccupied 
	}
}
//unsigned set_serial()
	
//}
#define VVV 14
void test0(){
	record_storage store = init_storage();
	{
		char const*const some[VVV] = {
			"engl",
			"fransis",
			"fransis",
			"bread",
			"china",
			"no_bread",
			"bread",
			"gagaga",
			"dasd",
	                "da",
			"ttt",
			"gg",
			"clcd",
			"krf",

			//"fransis",
	//		"china",
		};
	for (size_t i = 0; i < VVV; ++i) {
		record tmp_rec = init_a_record();
		set_a_record(&tmp_rec,some[i]);
		try_append_to_storage(&store,tmp_rec);
	}
	//record t0 = init_a_record();
	//char* str= "english";
//	set_a_record(&t0,str);
//	try_append_to_storage(&store,t0);
//	try_append_to_storage(&store,t0);
	/*
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


	//printf("what is that?? %s\n", (*(*(store.start_record)+0 )).key) ;
//printf("what is that?? %d\n", (*(*(store.start_record)+5 )).value) ;
	//printf("what is that?? %d\n", (*(*(store.start_record)+5 )).id) ;
	//printf("what is that?? %s\n", (*(*(store.start_record)+2 )).key) ;
	//printf("what is that?? %d\n", (*(*(store.start_record)+2 )).value) ;
	//printf("what is that?? %d\n", (*(*(store.start_record)+2 )).id) ;
	//printf("what is that?? %s\n", (*(*(store.start_record)+2 )).key) ;
	//free(store.start_record);
	//free(*(store.start_record));
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
