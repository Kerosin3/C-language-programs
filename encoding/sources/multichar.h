
typedef uint16_t char16_t;
typedef uint8_t char8_t;

enum char_type { cp,
    iso,
    koi,
    err };

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

void init_multichar(multichar*);
void assign_multichar(multichar*, char16_t utf8c, char8_t koi8c, char8_t isoc, char8_t cp1251c);
void init_multichar_store(multichar_store*);
void destroy_multichar_store(multichar_store*);
void append_to_multichar_store(multichar_store*, multichar);
char16_t find_match(multichar_store*, char8_t, enum char_type);
multichar get_some_multichar(multichar_store*, size_t);
