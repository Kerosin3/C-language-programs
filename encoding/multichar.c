#include "multichar.h"


void init_multichar(multichar* abstr_char){
	abstr_char -> utf8char = 0x00;
	abstr_char -> koi8char = 0x00;
	abstr_char -> iso8859char = 0x00;
	abstr_char -> cp1251char = 0x00;
}
void assign_multichar(multichar* abstr_char,char16_t utf8c, char16_t koi8c,char16_t isoc,char16_t cp1251c){
	abstr_char -> cp1251char = cp1251c;
	abstr_char -> iso8859char = isoc;
	abstr_char -> koi8char = koi8c;
	abstr_char -> utf8char = utf8c;
}
void init_multichar_store(multichar_store* multichar_array){
	multichar_array ->size =(unsigned) CHAR_STORE_LENGTH_MAX;
	multichar* store_ptr = NULL;
	(store_ptr =  (multichar*) calloc( CHAR_STORE_LENGTH_MAX,sizeof(multichar) )) ? printf("sucesfull allocation for array of chars"): printf("error while allocation\n"); ;
	multichar_array ->chars_store = store_ptr;
	multichar_array -> used = 0;
}
void destroy_multichar_store(multichar_store* array_of_chars){ //!! destructor
	free(array_of_chars->chars_store);
}
void append_to_multichar_store(multichar_store* multichar_array,multichar multi_char){
	unsigned long current_position	= multichar_array -> used; //get currently use n of objects
	multichar* ptr_pos = multichar_array ->chars_store;// main pointer
	printf("one pos is %p\n",ptr_pos);
	ptr_pos = ptr_pos + current_position; // add to pointer position
	printf("one pos is %p\n",ptr_pos);
	printf(" multichar val is %X\n",multi_char.cp1251char);
	*ptr_pos = multi_char; // assign value to storage
	printf(" multichar val  assign is %X\n",((multichar) *ptr_pos ).cp1251char );
	printf(" multichar val  pointer is %p\n",ptr_pos);
	multichar_array ->used++;
}

multichar* multichar_alloc() {   
	multichar* ptr = NULL;
	ptr = (multichar*) calloc(1,sizeof(multichar));
	if (!(ptr)) printf("eeror memory allocation\n");
	return ptr;
}
void multichar_destr(multichar* some_char){  // destructor!!!
	free(some_char);
}
// start from zero!
multichar get_some_multichar(multichar_store* storage, size_t n_th ){
	assert( n_th <= storage->used );
	assert( n_th >= 0 );
	multichar* ch0 = (multichar*)((storage->chars_store)+n_th);
	printf(" multichar val  pointer get is %p\n",ch0);
	printf(" multichar val get %X\n",ch0->cp1251char );
	return *ch0;
	
}


