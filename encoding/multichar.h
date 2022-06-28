#ifndef _stdint_indluded
#define _stdint_indluded 
#include <stdint.h>
#endif /* ifndef _stdint_indluded */
#ifndef stdlib_indluded
#include <stdio.h>
#define stdlib_indluded 
#endif /* ifndef stdlib_indluded */
#ifndef  MULTICHAR
#define MULTICHAR value
#define CHAR_STORE_LENGTH_MAX 70
#ifndef ASSERT_INDLUDED
#include <assert.h>
#endif /* ifndef ASSERT_INDLUDED */

typedef uint16_t char16_t;
typedef uint8_t char8_t;

/*! \enum char_type
 *
 *  Detailed description
 */
enum char_type { cp,iso,koi };

typedef struct {
	char16_t utf8char;
	char8_t koi8char;
	char8_t iso8859char;
	char8_t cp1251char;
} multichar;

typedef struct {
	unsigned long size;
	multichar* chars_store;
	unsigned long used;
} multichar_store; 

multichar* multichar_alloc();
void multichar_destr(multichar*);
void init_multichar(multichar*);
void assign_multichar(multichar*,char16_t utf8c, char8_t koi8c,char8_t isoc,char8_t cp1251c);
void assign_koi8(multichar*,char8_t koi8c);
void init_multichar_store(multichar_store*);
void destroy_multichar_store(multichar_store*);
void append_to_multichar_store(multichar_store*,multichar);
char16_t find_match(multichar_store*,char8_t,enum char_type);
multichar get_some_multichar(multichar_store*, size_t);

#endif /* ifndef  MULTICHAR */
