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
	//---------------------1 - utf8-----2 - koi8----3 - iso8859-------4 - cp1251-----------------//
	unsigned i = 0x0;
	char16_t a_letter_utf8 = 0xD090;
	char8_t a_letter_iso8859 = 0xB0;
	char8_t a_letter_cp1251 = 0xC0;
	char8_t a_letter_ko = 0x0;

	multichar a_char ;
	/*for (i = 0; i <= 63u; ++i) {
		if (i == 48u) {
			a_letter_utf8+=0xC0u;
			//a_letter_iso8859+=0xC0u;
			//a_letter_cp1251+=0xC0u;
			//a_letter_ko+=0xC0u;

		}
	a_char = ((multichar) set_one_char(a_letter_utf8,0xE1,a_letter_iso8859,a_letter_cp1251));
	append_to_multichar_store(&storage,\
			a_char); //
			printf("--------%d----------0x%X ",i,a_letter_cp1251);
			printf("-------utf8--------0x%X\n",a_letter_utf8);
			a_letter_utf8+=1u;
			a_letter_iso8859+=1u;
			a_letter_cp1251+=1u;
			a_letter_ko+=1u;
	} 
	*/
	for (i = 0; i <= 63u; ++i) {
	//append_to_multichar_store(&storage,
		if (i == 48u) {
			a_letter_utf8+=0xC0u;
			//a_letter_iso8859+=0xC0u;
			//a_letter_cp1251+=0xC0u;
			//a_letter_ko+=0xC0u;

		}

		if (i == 0) a_char = ((multichar) set_one_char(a_letter_utf8,0xE1,a_letter_iso8859,a_letter_cp1251));  //A
		if (i == 1) a_char = ((multichar) set_one_char(a_letter_utf8,0xE2,a_letter_iso8859,a_letter_cp1251)); //B
		if (i == 2) a_char = ((multichar) set_one_char(a_letter_utf8,0xF7,a_letter_iso8859,a_letter_cp1251)); //V
		if (i == 3) a_char = ((multichar) set_one_char(a_letter_utf8,0xE7,a_letter_iso8859,a_letter_cp1251));  //G
		if (i == 4) a_char = ((multichar) set_one_char(a_letter_utf8,0xE4,a_letter_iso8859,a_letter_cp1251));  //D
		if (i == 5) a_char = ((multichar) set_one_char(a_letter_utf8,0xE5,a_letter_iso8859,a_letter_cp1251));  //E
		if (i == 6) a_char = ((multichar) set_one_char(a_letter_utf8,0xF6,a_letter_iso8859,a_letter_cp1251));  //JE
		if (i == 7) a_char = ((multichar) set_one_char(a_letter_utf8,0xFA,a_letter_iso8859,a_letter_cp1251));  //Z
		if (i == 8) a_char = ((multichar) set_one_char(a_letter_utf8,0xE9,a_letter_iso8859,a_letter_cp1251));  //I
		if (i == 9) a_char = ((multichar) set_one_char(a_letter_utf8,0xEA,a_letter_iso8859,a_letter_cp1251));  //I kratki
		if (i == 10) a_char = ((multichar) set_one_char(a_letter_utf8,0xEB,a_letter_iso8859,a_letter_cp1251));  //K
		if (i == 11) a_char = ((multichar) set_one_char(a_letter_utf8,0xEC,a_letter_iso8859,a_letter_cp1251));  //L
		if (i == 12) a_char = ((multichar) set_one_char(a_letter_utf8,0xED,a_letter_iso8859,a_letter_cp1251));  //M
		if (i == 13) a_char = ((multichar) set_one_char(a_letter_utf8,0xEE,a_letter_iso8859,a_letter_cp1251));  //N
		if (i == 14) a_char = ((multichar) set_one_char(a_letter_utf8,0xEF,a_letter_iso8859,a_letter_cp1251));  //O
		if (i == 15) a_char = ((multichar) set_one_char(a_letter_utf8,0xF0,a_letter_iso8859,a_letter_cp1251));  //P
		if (i == 16) a_char = ((multichar) set_one_char(a_letter_utf8,0xF2,a_letter_iso8859,a_letter_cp1251));  //R
		if (i == 17) a_char = ((multichar) set_one_char(a_letter_utf8,0xF3,a_letter_iso8859,a_letter_cp1251));  //S
		if (i == 18) a_char = ((multichar) set_one_char(a_letter_utf8,0xF4,a_letter_iso8859,a_letter_cp1251));  //T
		if (i == 19) a_char = ((multichar) set_one_char(a_letter_utf8,0xF5,a_letter_iso8859,a_letter_cp1251));  //uy
		if (i == 20) a_char = ((multichar) set_one_char(a_letter_utf8,0xE6,a_letter_iso8859,a_letter_cp1251));  //F
		if (i == 21) a_char = ((multichar) set_one_char(a_letter_utf8,0xE8,a_letter_iso8859,a_letter_cp1251));  //X
		if (i == 22) a_char = ((multichar) set_one_char(a_letter_utf8,0xE3,a_letter_iso8859,a_letter_cp1251));  //TSE
		if (i == 23) a_char = ((multichar) set_one_char(a_letter_utf8,0xFE,a_letter_iso8859,a_letter_cp1251));  //TCHE
		if (i == 24) a_char = ((multichar) set_one_char(a_letter_utf8,0xFB,a_letter_iso8859,a_letter_cp1251));  //SHE
		if (i == 25) a_char = ((multichar) set_one_char(a_letter_utf8,0xFD,a_letter_iso8859,a_letter_cp1251));  //SHEeeee
		if (i == 26) a_char = ((multichar) set_one_char(a_letter_utf8,0xFF,a_letter_iso8859,a_letter_cp1251));  //tverdy znak
		if (i == 27) a_char = ((multichar) set_one_char(a_letter_utf8,0xF9,a_letter_iso8859,a_letter_cp1251));  //bI
		if (i == 28) a_char = ((multichar) set_one_char(a_letter_utf8,0xF8,a_letter_iso8859,a_letter_cp1251));  //magki znak
		if (i == 29) a_char = ((multichar) set_one_char(a_letter_utf8,0xFC,a_letter_iso8859,a_letter_cp1251));  //e
		if (i == 30) a_char = ((multichar) set_one_char(a_letter_utf8,0xE0,a_letter_iso8859,a_letter_cp1251));  //uy
		if (i == 31) a_char = ((multichar) set_one_char(a_letter_utf8,0xF1,a_letter_iso8859,a_letter_cp1251));  //ia
															//
															//
		if (i == 32) a_char = ((multichar) set_one_char(a_letter_utf8,0xE1u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //A
		if (i == 33) a_char = ((multichar) set_one_char(a_letter_utf8,0xE2u- 0x20u,a_letter_iso8859,a_letter_cp1251)); //B
		if (i == 34) a_char = ((multichar) set_one_char(a_letter_utf8,0xF7u- 0x20u,a_letter_iso8859,a_letter_cp1251)); //V
		if (i == 35) a_char = ((multichar) set_one_char(a_letter_utf8,0xE7u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //G
		if (i == 36) a_char = ((multichar) set_one_char(a_letter_utf8,0xE4u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //D
		if (i == 37) a_char = ((multichar) set_one_char(a_letter_utf8,0xE5u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //E
		if (i == 38) a_char = ((multichar) set_one_char(a_letter_utf8,0xF6u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //JE
		if (i == 39) a_char = ((multichar) set_one_char(a_letter_utf8,0xFAu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //Z
		if (i == 40) a_char = ((multichar) set_one_char(a_letter_utf8,0xE9u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //I
		if (i == 41) a_char = ((multichar) set_one_char(a_letter_utf8,0xEAu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //I kratki
		if (i == 42) a_char = ((multichar) set_one_char(a_letter_utf8,0xEBu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //K
		if (i == 43) a_char = ((multichar) set_one_char(a_letter_utf8,0xECu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //L
		if (i == 44) a_char = ((multichar) set_one_char(a_letter_utf8,0xEDu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //M
		if (i == 45) a_char = ((multichar) set_one_char(a_letter_utf8,0xEEu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //N
		if (i == 46) a_char = ((multichar) set_one_char(a_letter_utf8,0xEFu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //O
		if (i == 47) a_char = ((multichar) set_one_char(a_letter_utf8,0xF0u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //P
		if (i == 48) a_char = ((multichar) set_one_char(a_letter_utf8,0xF2u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //R
		if (i == 49) a_char = ((multichar) set_one_char(a_letter_utf8,0xF3u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //S
		if (i == 50) a_char = ((multichar) set_one_char(a_letter_utf8,0xF4u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //T
		if (i == 51) a_char = ((multichar) set_one_char(a_letter_utf8,0xF5u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //uy
		if (i == 52) a_char = ((multichar) set_one_char(a_letter_utf8,0xE6u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //F
		if (i == 53) a_char = ((multichar) set_one_char(a_letter_utf8,0xE8u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //X
		if (i == 54) a_char = ((multichar) set_one_char(a_letter_utf8,0xE3u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //TSE
		if (i == 55) a_char = ((multichar) set_one_char(a_letter_utf8,0xFEu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //TCHE
		if (i == 56) a_char = ((multichar) set_one_char(a_letter_utf8,0xFBu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //SHE
		if (i == 57) a_char = ((multichar) set_one_char(a_letter_utf8,0xFDu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //SHEeeee
		if (i == 58) a_char = ((multichar) set_one_char(a_letter_utf8,0xFFu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //tverdy znak
		if (i == 59) a_char = ((multichar) set_one_char(a_letter_utf8,0xF9u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //bI
		if (i == 60) a_char = ((multichar) set_one_char(a_letter_utf8,0xF8u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //magki znak
		if (i == 61) a_char = ((multichar) set_one_char(a_letter_utf8,0xFCu- 0x20u,a_letter_iso8859,a_letter_cp1251));  //e
		if (i == 62) a_char = ((multichar) set_one_char(a_letter_utf8,0xE0u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //uy
		if (i == 63) a_char = ((multichar) set_one_char(a_letter_utf8,0xF1u- 0x20u,a_letter_iso8859,a_letter_cp1251));  //ia

		//a_char = ((multichar) set_one_char(a_letter_utf8,0x00,a_letter_iso8859,a_letter_cp1251));  //ia
		append_to_multichar_store(&storage,\
			a_char); //
													   //
													   //
			a_letter_utf8++;
			a_letter_iso8859++;
			a_letter_cp1251++;
	}
	
//	append_to_multichar_store(&storage,\
			(multichar) set_one_char(0xD090,0xAB,0xAC,0xAD)); //
	//append_to_multichar_store(&storage,\
			(multichar) set_one_char(0xD091,0xCA,0xCE,0xCF));

	return storage;
}
