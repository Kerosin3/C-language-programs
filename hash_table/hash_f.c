#include "hash_f.h"
#define IS_UNSIGNED(t) ((t)~1 > 0)

static unsigned n_extends = 1;

void rehash_table(record_storage* storage);
static record_storage rehash_tablev2(record_storage* storage);
static void copy_obj(record_storage* storage,record a_record,unsigned long position);
unsigned long get_value_v2(record_storage* storage,const char* in_string);

unsigned long table_size = 10;
unsigned long long calc_hash(const char* input_string){
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
	//printf("copied string is %s, its length is %d \n",str_ptr,str_size);
	unsigned long long temp_c= 0;
	for (size_t i = 0; i < str_size; ++i) {// not includes null terminator
		temp_c+=( ((uint8_t) str_ptr[i] ) * pow(((unsigned) SALT),i)  ); // unicode is always 7 byte with leading zero
		//printf("value is 0x%X, your hash is %llu\n",(uint8_t) str_ptr[i],temp_c);
	}
	printf("calced hash value:%llu \n",temp_c);
	return temp_c;
	
}
unsigned long long rehash(unsigned long long in_hash){
	printf("calcing new has value.....\n");
	int str_len = snprintf(NULL,0,"%u",in_hash);// get the size
	str_len++ ;//space for null term
	//char* str_converted = malloc(str_len);
	char* str_converted = alloca(str_len);
	if (!(str_converted)) {
		printf("errror memory allocation\n");
		exit(1);
	}
	snprintf(str_converted,str_len,"%d",in_hash);
	unsigned long long new_hash = calc_hash(str_converted);
	printf("----------prev hash value %llu---------new hash value is %llu \n",in_hash,new_hash);
	//free(str_converted); // free memory
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

record_storage init_storage(unsigned max_size_init){
	record_storage storage;
	storage.current_size = 0;
	storage.max_size= max_size_init;
	record** pt_first = calloc(sizeof(record*), 1); // allocate one main pointer
	*pt_first = calloc(sizeof(record), max_size_init);  // allocate space for max_size pointers to 1 record   calloc(sizeof(record)*n,10) -- 10 pointers to 10 record
	if ( !(pt_first) || !(*pt_first) ) {
		printf("error memory allocation, aborting\n");
		exit(1);
	}// WTF???
	storage.start_record = pt_first;
	//storage.start_record = (record*) calloc(1, sizeof(record));
	return storage;
}
void storage_destroy(record_storage* storage ){
	printf("destroying. storage size %d.\n",storage->max_size);
	unsigned tp =0;
	for (size_t i = 0; i < storage->max_size; ++i) {
		if (   ((*(*(storage->start_record)+tp)).flag)>0 ) {
			free(  ((*(*(storage->start_record)+tp)).key)    );
		}
			tp++;
	}
	free(*(storage->start_record));
	*(storage->start_record) = NULL;
	//
	free((storage->start_record));// ??? OK??
	storage->start_record = NULL;
	// CHECK WHETHER NOT DOUBLE FREEE
	printf("freed %d objects\n",tp); 
}
//create a destructor??..
void set_a_record(record* rec_ptr,const char* in_string){
	unsigned str_l = strlen(in_string); // dangerous
	str_l++; //null terminator
	printf("here %s %d \n",in_string,str_l);
	//char* ptr = aligned_alloc(256,sizeof(uint8_t)*str_l);
	//char* ptr = calloc(str_l,sizeof(char));
	char* ptr = malloc(sizeof(char)* str_l); //-------------??????
	printf("???????\n");
	if (!(ptr)){
		printf("cannot allocate memore, aborting\n");
		exit(1);
	}
	ptr[str_l]='\0';
	strcpy(ptr,in_string);
	rec_ptr->key=ptr;
	rec_ptr->id = calc_hash(ptr); //assign hash
	//printf("has value inside is %llu\n",rec_ptr->id);
	printf("copied string is %s\n",rec_ptr->key);
	printf("lenths are %d %d \n",strlen(in_string),strlen(rec_ptr->key));
	rec_ptr->value = 1;
}

void destroy_a_record(record* rec_ptr){
	
}
signed check_occupy(record_storage* storage,unsigned long position){
	printf("checking.1. postition %d, storage:%p\n",position,storage);
	printf("pointer is %p \n", &((*(*(storage->start_record)+position)).flag  ) );
	enum flag_written flag = (*(*(storage->start_record)+position)).flag; //check whether its writtne
	//enum flag_witten flag =  (*(*(storage->start_record)+position)).flag;
	printf("checking.2..\n");
	if (flag>0) { //written or moved
		return 1;
	} else if (flag==0){ //empty
		return 0;
	} else {
		return -1;
	}
	
} 


unsigned try_append_to_storage(record_storage* storage,record a_record){
	printf("aaa\n");
	if ((storage->current_size) >= (storage->max_size)){
		printf("===============current size %lu===================expanding the table by 10 entries!!!!!!!==================================\n",storage->max_size);
		record** pt_old = storage->start_record; // store old ptr
		storage->start_record =  rehash_tablev2(storage).start_record;
//		storage_destroy(storage); // destroy the old storage
		storage->max_size = n_extends * 10;
		storage->current_size = (n_extends-1) * 10;
		//storage->current_size= filled_size; // add value
		//free(*storage->start_record); //free old*
		free(*pt_old); //free old*
		free(pt_old); //free old

		*pt_old = NULL;
		pt_old = NULL;
		printf("==================================expanding done==================================\n");

	}
	unsigned long long new_hash;
	new_hash = 0;
	//unsigned long long *hash_ptr = &record.id;
jump_0:
	unsigned long tposition =   (a_record.id) % ( (storage->max_size)  ); // calc position in the table MUNUS ONE?
	printf("============has value after jump:%llu, position is %u, string %s \n",new_hash,tposition,a_record.key);
	printf("positi hash is %llu \n",a_record.id);
	unsigned long cur_position = tposition;
	signed occupied =0;
	unsigned flag_zero = 0;
	printf("element show:%d element key is %s\n",a_record.flag, a_record.key);
	printf("test, store adress %p \n",storage);
	occupied =check_occupy(storage,cur_position); //check whether position is occupied???
	printf("occupied?= %d \n",occupied);
	record* cur_rec_pos = &(*(*(storage->start_record)+tposition)); 
	//printf("11 values are %p and %p \n",(void*) &cur_rec_pos,(void*) &(*(*(storage->start_record)+tposition))  );
	if (occupied >= 1 && (!(flag_zero)))  { //written or moved
		if (!(check_position(storage,&a_record,tposition))) { // not equal & occupied!
			printf("collision!!!!\n");			
			new_hash = rehash(a_record.id); // calc new hash value
			a_record.id = new_hash; //assign new hash
			printf("goto->>>>>\n");
			a_record.flag = moved; // mark as moved
			flag_zero = 1;
			goto jump_0; // go an find a space in table
		} else { // equal  and occupied!  -> ADD COUNT!
	        	printf("occur is storagexxxxxxxxxxxxxxxxxx: %ld\n",cur_rec_pos->value  );
			cur_rec_pos->value++;
		}
	} else if (occupied==0) {// if not ocuppied
		if (flag_zero) {
			a_record.flag = moved;
		} else {
			a_record.flag = written;
		}
		printf("add new entry %s \n",a_record.key);
		printf("storage address %p\n",(void*) storage);
		copy_obj(storage,a_record,cur_position);
		storage->current_size++;
	} else { //moved... and flag zero
		a_record.flag = moved;
		printf("add new entry moved %s \n",a_record.key);
		copy_obj(storage,a_record,cur_position);
		printf("I AM HERE________________________\n");
	}
	printf("storage address %p\n",(void*) storage);
	printf("values are %p and %p \n",(void*) cur_rec_pos,(void*) &(*(*(storage->start_record)+tposition))  );
	printf("<><><><><><><><>position is %d tpos %d, inside: %s, position in table: %u, occur: %lu ,written? = %d \n",
			cur_position,
			tposition,
			cur_rec_pos->key,
			tposition, 
			cur_rec_pos->value,   
			cur_rec_pos->flag
			) ;
	char* test = (*((*(storage->start_record)+cur_position))   ).key;   
	printf("hash: %llu\n",(*((*(storage->start_record)+cur_position))   ).id);
	printf("append to a poisititon %lu , key is %s \n", cur_position, (*((*(storage->start_record)+cur_position))).key  );
	printf("----------------table size is %d-------filled size is %llu--------------------\n",storage->max_size,storage->current_size);
	printf("-------------------------------------------\n");
}

static record_storage rehash_tablev2(record_storage* storage){
	printf("statring table expansion!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	unsigned long index = 0;
//	record* stored_rec = (*(storage->start_record)+index); ?????
//	printf("hmmmm = %s\n",(*(storage->start_record)+1)->key);
	//--////-----------
	printf("iterate over %d \n",storage->max_size);
	n_extends++;
	record_storage new_storage = init_storage( (n_extends)*10 )  ; // create new storage 
	//-------------
	size_t j = 0;
	for (size_t i = 0; i < storage->max_size; ++i) { // iterate over old storage
			index = i;
			record* stored_rec = (*(storage->start_record)+index); // ????
		//	record c_record = *stored_rec; // take record
			printf("adress is %p \n",(void*) stored_rec);
			printf("new storage size if %llu \n",new_storage.max_size);
			printf("current index is %d\n",index);
			printf("aapending %s \n", stored_rec->key );
			try_append_to_storage(&new_storage, *stored_rec  ); // append to new storage with new size
			printf("appended key %s  \n",stored_rec->key) ;
//			printf("in storage %s \n",  ((*(*(new_storage.start_record)+index)).value));
			//free(stored_rec->key);
			//free(  ((*(*(storage->start_record)+i)).key)    );
			j = i;
	//-------------
		//}
	}
	printf("iterated over %d items\n",j+1);
	printf("table size after expand is %lu \n",new_storage.max_size);
	//free(*pt_old); //free old*
	//free(pt_old); //free old
	//pt_old = NULL;
	return new_storage;
}


void rehash_table(record_storage* storage){
	printf("==============================rehashing the whole table=====================================\n");
	unsigned index = 0;
	unsigned long n_pos = 0;
	record* stored_rec = (*(storage->start_record)+index);
	unsigned long long first_hash = 0;
	do {
		if  (stored_rec->flag > 0)  printf("-----------------analyzing:%s-----%d----------------\n",stored_rec->key,stored_rec->flag);
		if (  (stored_rec)->flag  == 1 ){ // flag written
					   ; // skip
		} else if ( (stored_rec->flag) >1 ) { //moved
			unsigned long lt = 0;
			unsigned flg = 0;
			do {
				/*if (lt >= storage->max_size) {
					printf("not enought space!!!!index = %d abort!!!\n",lt);
					exit(1);
				}*/
				if (!(first_hash)){ // once calc initial hash
					first_hash = calc_hash(stored_rec->key); // calc initial hash
					n_pos =   (first_hash) % ( (storage->max_size)  ); //calc new postion
					flg = 1;
				} else { //next time rehash
					first_hash = rehash(first_hash);
					n_pos =   (first_hash) % ( (storage->max_size)  ); //calc new postion
					flg = 0;
				}
				printf("<<<<<<<<p=%llu\n",n_pos);
				lt++;
			} while( ( check_occupy(storage,n_pos) ) != 0); // while empty not found
			if (flg) {
				stored_rec->flag=written;
			} else {
				stored_rec->flag=moved;
			}
			copy_obj(storage,*stored_rec,n_pos); // copy to the new position
			stored_rec->id = calc_hash(stored_rec->key);  //assign new hash
			printf(">>>>>>>>>>>>>>>assigned new postion:%llu,hash:%lld,key:%s, flag=%d \n",n_pos,stored_rec->id,stored_rec->key,stored_rec->flag)	;

		} else { // empty
			;
		}
		index++;
		stored_rec = (*(storage->start_record)+index);
	} while( index < storage->max_size  );
	printf("=====================rehashing done===========================\n");
}

unsigned check_null_str(char* in_str){
	printf("analyze null\n");
	if ((in_str == NULL) || (in_str[0] == '\0')) {
	   printf("c is empty\n");
	   return 1;
	}
	printf("not epmty!\n");
	return 0;
}




unsigned long get_value_v2(record_storage* storage,const char* in_string){

	unsigned long limit = 0;
	unsigned long long _init_hash = calc_hash(in_string);
	unsigned magic_posit = (_init_hash) % ( (storage->max_size)  ); // get first try
	record* stored_rec = (*(storage->start_record)+magic_posit);
	printf("address is %p contain %s \n" , stored_rec,  (*(storage->start_record)+magic_posit)->key  );
	
	printf("initial try to find %s its hash:%llu ,suggest position:%d  max_size = %d \n",in_string,_init_hash,magic_posit,storage->max_size);
	if (check_null_str(stored_rec->key)){ // if null
		printf("go jump rehash\n");
		goto jump_rehash;
		//_init_hash = rehash(_init_hash);
	} else {
		printf("trying first! \n");
		printf("comparing %s with %s \n",stored_rec->key,in_string);
		int first_comp = strcmp(stored_rec->key,in_string); // try first!
		if (!(first_comp)) {
			printf("found!!!\n");
			return magic_posit ; // the same ;!!!! WIN FIRST OCCURENCE
		}				     // 
	}
jump_rehash:
	do {// work while NULL
		_init_hash = rehash(_init_hash);
		magic_posit = _init_hash % ( storage->max_size ); 
		stored_rec = (*(storage->start_record)+magic_posit); // ???? hehe
		printf("magic=%d look  %p \n",magic_posit,stored_rec);
	} while ((check_null_str(stored_rec->key))); // repeat while empty
	printf("look %s \n",stored_rec->key);
	//printf("string on postition %s base is  %s \n",stored_rec->key);
	if (!( strcmp(stored_rec->key,in_string))) { // not null here!!! 
		return magic_posit;
	} else { // not equal but not null!
		goto jump_rehash;
	}


}
/*
unsigned long get_value(record_storage* storage,char* in_string){
	unsigned the_magic_limit = (n_extends+1) * 2000000;
	//printf("input string %s, compared with %s\n",in_string, stored_rec -> key);
	jump_rehash:
	do{
		magic_posit = _init_hash % ( storage->max_size ); 
		_init_hash = rehash(_init_hash);

	}while(check_null_str(stored_rec->key)); // work while NULL

	while(  !( strcmp(stored_rec->key,in_string)    )) { // not null here! done when the same
		if (stored_rec->key)  { //written or moved
		//magic_posit = _init_hash % ( storage->max_size ); 
		//_init_hash = rehash(_init_hash);
		limit++;
		printf("suggest posit %d ,in string: %s value %s \n",magic_posit, in_string,  (*(storage->start_record)+magic_posit)->key  );
		//cond = (fl) ? (1) : !( strcmp(stored_rec->key,in_string)  ) ; 
		goto jump_rehash;
		} else {
			continue;
		}
	}

	return magic_posit;
}
*/
static void copy_obj(record_storage* storage,record a_record,unsigned long position){
	unsigned s_len = strlen(a_record.key)  ; 
	printf("xxxcopying obj: %s\n",a_record.key);
	//int s_len = snprintf(NULL,0,"{data:%c}",a_record.key);// get the size
	printf("the len is %d\n",s_len);
	assert(s_len > 0);
	s_len++; // add space for null term
	//char* s_tmp = aligned_alloc(2,s_len*sizeof(char));
	char* s_tmp = calloc(sizeof(char), s_len); //allocate memory for string
	//char* s_tmp = malloc(sizeof(char)* s_len); //allocate memory for string
	printf("khe\n");
	if (!(s_tmp)) {
		printf("error memeory allocation\n");
		exit(1);
	}
	strncpy( s_tmp,a_record.key, s_len-1 );
	s_tmp[s_len] = '\0';
	record* target_record = ((*(storage->start_record)+position));
	target_record->id = a_record.id;
	target_record->value =  a_record.value;
	target_record->flag = a_record.flag;
	target_record->key =  s_tmp;
	printf("copying done, string= %s\n", (char*) (*((*(storage->start_record)+position))).key  );
}

//record get_a_record(char* check_this_input){
unsigned check_position(record_storage* storage,record* a_record,unsigned long try_this_position){ // whether it is already occupied
	printf("gegege\n");
	char* string_on_this_position =  (*((*(storage->start_record)+try_this_position))).key ;
	char* string_to_check =  a_record->key;
//	if (!(string_on_this_position == NULL)) 
	printf("checkoing position %lu\n",try_this_position);
	printf("string to check--------------------------%s\n",string_to_check);
	printf("testx\n");
	printf("string on position>>>>>>>>>>>>>>>>>>>>>>>>%s\n",string_on_this_position);
	int rez = -1;
	if (string_on_this_position != NULL ){
		printf("kkkkkkkkkkkkkkkk\n");
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
#define VVV 15
void test0(){
	record_storage store = init_storage(10);
	{
		char const*const some[VVV] = {
			"engl",
			"fransis",
			"fransis",
			"bread",
			"china",
			"no_bread",
			"bread",
			"gagagat",
			"dasd",
	                "da",
			"ttt",
			"gg",
			"clcd",
			"krf",
			"русское",

			//"fransis",
	//		"china",
		};
		for (size_t i = 0; i < VVV; ++i) {
		record tmp_rec = init_a_record();
		set_a_record(&tmp_rec,some[i]);
		try_append_to_storage(&store,tmp_rec);
	}
	//printf("fransis %s\n", (*(*(store.start_record)+2 )).key) ;
	//printf("fransis %d\n", (*(*(store.start_record)+2 )).id) ;
	//printf("nth positions:%d containts %s\n",12, (*(*(store.start_record)+12 )).key) ;
//	printf("<><><><><><><><><><><><><><><> fransis position:   %d\n",get_value(&store, some[13] ));
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	for (size_t i = 0; i < VVV; i++) {
		printf("%d we are searching %s \n",i,some[i]);
		unsigned long long getted_value = get_value_v2(&store, some[i] );  // position
		printf("---\n");
		record contained = (*(*(store.start_record)+getted_value )) ;
		printf("searched %s, found on position %llu, contains %s, meet %d \n",some[i], getted_value ,contained.key, contained.value) ;

	printf("----------\n");
	}
	//printout_content(&store);
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
