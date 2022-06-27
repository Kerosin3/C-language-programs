//#define chars_table
#include "chars_table.h"
//#include "multichar.h"
 
//assign_multichar(&mchar01,0xAA,0xAB,0xAC,0xAD);
multichar_store multichar_collection_init(){
	multichar_store storage; // declare storage
	init_multichar_store(&storage); //init storage
				       //
	multichar char01;
	init_multichar(&char01);
	assign_multichar(&char01,0xAA,0xAB,0xAC,0xAD)	;

	append_to_multichar_store(&storage,char01);
	return storage;
}
