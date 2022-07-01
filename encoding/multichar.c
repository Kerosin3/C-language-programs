//#include "multichar.h"
#include "includes.h"


void init_multichar(multichar* abstr_char){
	abstr_char -> utf8char = 0x00;
	abstr_char -> koi8char = 0x00;
	abstr_char -> iso8859char = 0x00;
	abstr_char -> cp1251char = 0x00;
}
void assign_multichar(multichar* abstr_char,char16_t utf8c, char8_t koi8c,char8_t isoc,char8_t cp1251c){
	abstr_char -> cp1251char = cp1251c;
	abstr_char -> iso8859char = isoc;
	abstr_char -> koi8char = koi8c;
	abstr_char -> utf8char = utf8c;
}
void init_multichar_store(multichar_store* multichar_array){
	multichar_array ->size =(unsigned) CHAR_STORE_LENGTH_MAX;
	multichar* store_ptr = NULL;
	(store_ptr =  (multichar*) calloc( CHAR_STORE_LENGTH_MAX,sizeof(multichar) )) ? printf("sucesfull allocation for array of chars\n"): printf("error while allocation\n"); ;
	multichar_array ->chars_store = store_ptr;
	multichar_array -> used = 0;
}
void destroy_multichar_store(multichar_store* array_of_chars){ //!! destructor
	free(array_of_chars->chars_store);
}
char16_t find_match(multichar_store* storage, char8_t a_char, enum char_type c_t){
	unsigned long store_size = (storage-> used) ;
	assert(store_size != 0); // at least one element should be
	multichar* mchar;
	unsigned long i =0 ;
	switch (c_t) {
		case 0: //cp1251
			while (i < store_size){
			mchar = (multichar*) ((storage->chars_store)+i);
			char8_t actual_char = mchar ->cp1251char; 
			if (actual_char == a_char) return mchar->utf8char;
				//multichar* ch0 = (multichar*)((storage->chars_store)+n_th);
			i++;
		} 	
			return a_char;

			break;
		case 1: //iso
			while (i < store_size){
			mchar = (multichar*) ((storage->chars_store)+i);
			char8_t actual_char = mchar ->iso8859char; 
			if (actual_char == a_char) return mchar->utf8char;
				//multichar* ch0 = (multichar*)((storage->chars_store)+n_th);
			i++;
		} 	
			return a_char;
			break;
		case 2: //koi
			while (i < store_size){
			mchar = (multichar*) ((storage->chars_store)+i);
			char8_t actual_char = mchar ->koi8char; 
			if (actual_char == a_char) return mchar->utf8char;
				//multichar* ch0 = (multichar*)((storage->chars_store)+n_th);
			i++;
		} 	
			return a_char;
			break;

		default:
			printf("not matching cases... something gone wrong\n");
			break;
			
	}
			
}


void append_to_multichar_store(multichar_store* multichar_array,multichar multi_char){
	unsigned long current_position	= multichar_array -> used; //get currently use n of objects
	multichar* ptr_pos = multichar_array ->chars_store;// main pointer
	ptr_pos = ptr_pos + current_position; // add to pointer position
	*ptr_pos = multi_char; // assign value to storage
	multichar_array ->used++;
}

// start from zero!
multichar get_some_multichar(multichar_store* storage, size_t n_th ){
	assert( n_th <= storage->used );
	assert( n_th >= 0 );
	multichar* ch0 = (multichar*)((storage->chars_store)+n_th);
	return *ch0;
	
}


