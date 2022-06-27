//#define chars_table
#include "chars_table.h"
#include "multichar.h"
//inline multichar set_one_char();
static inline multichar set_one_char(char16_t utf8c,   char16_t koi8c ,\
		       char16_t iso8859c, char16_t  cp1251c ){ // private
	multichar some_char;
	init_multichar(&some_char);
	assign_multichar(&some_char, \
			utf8c, \
			koi8c, \
			iso8859c,\
			cp1251c );
	return some_char;
}

//assign_multichar(&mchar01,0xAA,0xAB,0xAC,0xAD);
multichar_store multichar_collection_init(){
	multichar_store storage; // declare storage
	init_multichar_store(&storage); //init storage
				       //
	//multichar char01;
	//init_multichar(&char01);
	
	//assign_multichar(&char01,0xAA,0xAB,0xAC,0xAD)	;
	
	append_to_multichar_store(&storage,\
			(multichar) set_one_char(0xAA,0xAB,0xAC,0xAD));
	append_to_multichar_store(&storage,\
			(multichar) set_one_char(0xCC,0xCA,0xCE,0xCF));

	return storage;
}
