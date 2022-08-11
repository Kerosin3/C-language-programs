#include "hash_f.h"
#define IS_UNSIGNED(t) ((t)~1 > 0)
#define EXTENS_N 10000
//#define DEBUG
#define SIDE_LIBS 1  // set 0 for "naive" hash function usage

//#warning this programm runs on x86_64 arch 64 bit
#pragma message "starting copilation!!"

_Static_assert(sizeof(uint64_t) == sizeof(unsigned long long),
               "uint64_t and unsigned long sizes are not matched,aborting...\n");
_Static_assert(sizeof(char) == sizeof(uint8_t), "uint8_t and char sizes are not matched,aborting...\n");

static unsigned n_extends = 1;
#if SIDE_LIBS == 1
static uint64_t seed0 = 0xabcdef;
#endif

void rehash_table(record_storage *storage);
static record_storage rehash_tablev2(record_storage *storage);
static void copy_obj(record_storage *storage, record a_record, unsigned long position);
unsigned long get_value_v2(record_storage *storage, const char *in_string);
unsigned long long raise_p(unsigned long long in_arg, size_t times);
unsigned long long calc_hash2(const char *);
unsigned long long rehash2(unsigned long long);

#if SIDE_LIBS == 1
#pragma message "sidelibs are included!"
unsigned long long calc_hash(const char *input_string)
{
    uint64_t hash64 = spookyhash_64(input_string, strlen(input_string), seed0);
    return (unsigned long long)hash64;
}
#endif

#if SIDE_LIBS == 0
#pragma message "sidelibs are not included!"
unsigned long long calc_hash(const char *input_string)
{
    if ((sizeof(uint8_t) != (sizeof(char))))
    {
        printf("platform error!,aborting...\n");
        return 0;
    }
    char const *str_ptr = input_string; // its ok
    size_t str_size = strlen(str_ptr);  // size of analyzed string
    printf("your string %s length is %lu \n", input_string, str_size);
    unsigned long long temp_c = 0;
    for (size_t i = 0; i < str_size; ++i)
    { // not includes null terminator
        // printf("--------\n");
        unsigned long long pow_rez = raise_p(SALT, i);
        // unsigned long long pow_rez = (unsigned long long)  pow(SALT,i); //double overflow error!!!
        temp_c = ((unsigned long long)(((unsigned long long)((unsigned char)str_ptr[i])) * pow_rez
                                       //( (unsigned long long)  pow(((unsigned) SALT),i)  )
                                       )); // unicode is always 7 byte with leading zero
        // printf("current char is %u calced val is %llu,i'th: %lu pow val is %llu \n",(unsigned char)
        // ((str_ptr[i])),temp_c,i,pow_rez  );
        temp_c += temp_c;
    }
    temp_c += str_size;
    printf("we calced hash value for input string %s :%llu\n", input_string, temp_c);
#ifdef DEBUG
#endif
    return temp_c;
}
#endif

unsigned long long raise_p(unsigned long long in_arg, size_t times)
{
    size_t i = 0;
    unsigned long long base = in_arg;
    if (!(times))
        return 1; // zero times
    times--;
    // printf("times is %lu, base = %llu \n",times,in_arg);
    for (i = 0; i < times; ++i)
    {
        in_arg *= base;
        // printf("%i-- %llu \n",i,in_arg);
    }

    return in_arg;
}

#if SIDE_LIBS == 0
unsigned long long rehash(unsigned long long in_hash)
{
    int str_len = snprintf(NULL, 0, "%llu", in_hash); // get the size
    str_len++;                                        // space for null term
    char *str_converted = alloca(str_len);
    if (!(str_converted))
    {
        printf("errror memory allocation\n");
        exit(1);
    }
    snprintf(str_converted, str_len, "%llu", in_hash);
    str_converted[str_len] = '\0';
    unsigned long long new_hash = calc_hash(str_converted);
    printf("--rehash--previous hash value %llu,new hash value is %llu \n", in_hash, new_hash);
    // free(str_converted); // free memory
    return new_hash;
}
#endif

#if SIDE_LIBS == 1
unsigned long long rehash(unsigned long long in_num)
{
    char *str_placer = alloca(21 + 1);
    snprintf(str_placer, 21 + 1, "%llu", in_num);
    str_placer[21] = '\0';
    uint64_t rehash = spookyhash_64((void *)str_placer, strlen(str_placer), seed0);
    return (unsigned long long)rehash;
}
#endif

record init_a_record()
{
    record a_record;
    a_record.id = 0;
    a_record.key = '\0';
    a_record.value = 0;
    a_record.flag = not_written;
    return a_record;
}

record_storage init_storage(unsigned max_size_init)
{
    record_storage storage;
    storage.current_size = 0;
    storage.max_size = max_size_init;
    record **pt_first = calloc(sizeof(record *), 1);   // allocate one main pointer
    *pt_first = calloc(sizeof(record), max_size_init); // allocate space for max_size pointers to 1 record
                                                       // calloc(sizeof(record)*n,10) -- 10 pointers to 10 record
    if (!(pt_first) || !(*pt_first))
    {
        printf("error memory allocation, aborting\n");
        exit(1);
    } // WTF???
    storage.start_record = pt_first;
    return storage;
}
void storage_destroy(record_storage *storage)
{
    size_t i = 0;
    size_t j = 0;
    for (i = 0; i < storage->max_size; ++i)
    {
        if (((*(*(storage->start_record) + i)).flag) > 0)
        {
            free(((*(*(storage->start_record) + i)).key));
            (*(*(storage->start_record) + i)).key = (void *)0;
            j++;
        }
    }
    free(*(storage->start_record));
    *(storage->start_record) = (void *)0;
    free((storage->start_record)); // ??? OK??
    storage->start_record = (void *)0;
    // CHECK WHETHER NOT DOUBLE FREEE
    printf("destroying storage size is %lu.\n", storage->max_size);
    printf("freed %lu objects\n", j);
}
// create a destructor??..
void set_a_record(record *rec_ptr, const char *in_string)
{
    unsigned str_l = strlen(in_string); // dangerous
    str_l++;                            // null terminator
#ifdef DEBUG
    printf("setting a record with key %s, its length is %u \n", in_string, str_l);
#endif
    // char* ptr = aligned_alloc(256,sizeof(uint8_t)*str_l);
    char *const ptr = calloc(str_l, sizeof(char));
    // char* ptr = malloc(sizeof(char)* str_l); //-------------??????
    if (!(ptr))
    {
        printf("cannot allocate memore, aborting\n");
        exit(1);
    }
    strncpy(ptr, in_string, str_l);
    ptr[str_l - 1] = '\0';
    rec_ptr->key = ptr;
    rec_ptr->id = calc_hash(ptr); // assign hash
#ifdef DEBUG
    printf("copied string is %s\n", rec_ptr->key);
    printf("lenths are %d %d \n", strlen(in_string), strlen(rec_ptr->key));
#endif
    rec_ptr->value = 1; // initial
}

signed check_occupy(record_storage *storage, unsigned long position)
{
    enum flag_written flag = (*(*(storage->start_record) + position)).flag; // check whether its writtne
    if (flag > 0)
    { // written or moved
        return 1;
    }
    else if (flag == 0)
    { // empty
        return 0;
    }
    else
    {
        return -1;
    }
}

unsigned try_append_to_storage(record_storage *storage, record a_record)
{
#ifdef DEBUG
    printf("supplied string is %s\n", a_record.key);
#endif
    if ((storage->current_size) == ((storage->max_size)))
    {
        printf("===============current size %lu===================expanding the table by 10 "
               "entries!!!!!!!==================================\n",
               storage->max_size);
        record_storage new_storage = rehash_tablev2(storage); // create new storage
        storage_destroy(storage);                             // destroy the old storage
        *storage = new_storage;
        printf("==================================expanding done==================================\n");
    }
    unsigned long tposition = (a_record.id) % ((storage->max_size)); // calc position in the table MUNUS ONE?
#ifdef DEBUG
    printf("maxsizeis %lu,fulledsize is %lu \n", storage->max_size, storage->current_size);
    printf("->hash rec hash value is %llu,suggest position is %lu, string %s \n", a_record.id, tposition, a_record.key);
#endif
    unsigned long cur_position = tposition;
    signed occupied = 0;
    unsigned flag_zero = 0;
    occupied = check_occupy(storage, cur_position); // check whether position is occupied???
    record *cur_rec_pos = &(*(*(storage->start_record) + tposition));
    if (occupied >= 1 && (!(flag_zero)))
    { // written or moved
        if (!(check_position(storage, &a_record, tposition)))
        { // not equal & occupied!
#ifdef DEBUG
            printf(">>>>collision occured, starting rehashing..\n");
            printf("goto->>>>>\n");
#endif
            // new_hash = rehash(a_record.id); // calc new hash value
	    unsigned ii = 0;
	    unsigned k  = 7;
	    printf("collision occured! %s \n",a_record.key);
	    do {
		ii++;
		tposition = (a_record.id + (ii*k)  ) % (storage->max_size); // some magic
            	cur_rec_pos = &(*(*(storage->start_record) + tposition));
		printf("------->>try %u, postition %lu contains %s \n",ii,tposition,cur_rec_pos->key);
	       } while ( ( cur_rec_pos->key  ));
            a_record.flag = moved;             // mark as moved
	    cur_position = tposition;
            copy_obj(storage, a_record, cur_position);
            flag_zero = 1;
        }
        else
        { // equal  and occupied!  -> ADD COUNT!
#ifdef DEBUG
            printf("this word is already exisits, adding count: %ld\n", cur_rec_pos->value);
#endif
            cur_rec_pos->value++;
        }
    }
    else if (occupied == 0)
    { // if not ocuppied
        if (flag_zero)
        {
            a_record.flag = moved;
        }
        else
        {
            a_record.flag = written;
        }
#ifdef DEBUG
        printf("found empty entry, adding new entry %s \n", a_record.key);
#endif
        copy_obj(storage, a_record, cur_position);
        storage->current_size++;
    }
    else
    { // moved... and flag zero
        a_record.flag = moved;
#ifdef DEBUG
        printf("adding entry moved %s \n", a_record.key);
#endif
        copy_obj(storage, a_record, cur_position);
    }
//#ifdef DEBUG
    printf("<><><><><><><>%d<>position is %lu filled_n %lu, inside: %s, position in table: %lu, occur: %lu ,written? = "
           "%d  hash %llu\n",
           n_extends, cur_position, storage->current_size, cur_rec_pos->key, tposition, cur_rec_pos->value,
           cur_rec_pos->flag, cur_rec_pos->id);
    printf("-------------------------------------------\n");
//#endif
    return 1;
}

static record_storage rehash_tablev2(record_storage *storage)
{
    printf("starting table expansion!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    n_extends++;
    record_storage new_storage = init_storage((n_extends)*EXTENS_N); // create new storage
#ifdef DEBUG
    for (size_t i = 0; i < (storage->max_size); ++i)
    {
        record *stored_rec = (*(storage->start_record) + i); // ????
        printf("full cont %lu is %s\n", i, stored_rec->key);
    }
#endif
    size_t index = 0;
    for (index = 0; index < (storage->max_size); ++index)
    {                                                            // iterate over old storage
        record *stored_rec = (*(storage->start_record) + index); // ????
#ifdef DEBUG
        printf("->cycle>>>>>>adress is %p \n", (void *)stored_rec);
        printf("new storage size if %llu \n", new_storage.max_size);
        printf("current index is %d\n", index);
        printf("index=%d aapending %s \n", index, stored_rec->key);
#endif
        try_append_to_storage(&new_storage, *stored_rec); // append to new storage with new size
#ifdef DEBUG
        printf("appended keyd %s  \n", stored_rec->key);
#endif
    }
#ifdef DEBUG
    printf("iterated over %d items\n", index + 1);
    printf("table size after expand is %llu, cur size is %llu \n", new_storage.max_size, new_storage.current_size);
#endif
    return new_storage;
}

unsigned check_null_str(const char *in_str)
{
    if ((in_str == NULL) || (in_str[0] == '\0'))
    {
        // printf("c is empty\n");
        return 1;
    }
    // printf("not empty!\n");
    return 0;
}

unsigned long get_value_v2(record_storage *storage, const char *in_string)
{
    unsigned long long _init_hash = calc_hash(in_string);
    unsigned long magic_posit = (_init_hash) % ((storage->max_size)); // get first try
    record *stored_rec = (*(storage->start_record) + magic_posit);
    printf("address is %p contain %s \n", (void *)stored_rec, (*(storage->start_record) + magic_posit)->key);

    printf("initial try to find %s its hash:%llu ,suggest position:%lu  max_size = %lu \n", in_string, _init_hash,
           magic_posit, storage->max_size);
    if (check_null_str(stored_rec->key))
    { // if null
        printf("go jump rehash\n");
        goto jump_rehash;
    }
    else
    {
        printf("trying first! \n");
        printf("comparing %s with %s \n", stored_rec->key, in_string);
        int first_comp = strcmp(stored_rec->key, in_string); // try first!
        if (!(first_comp))
        {
            printf("found!!!\n");
            return magic_posit; // the same ;!!!! WIN FIRST OCCURENCE
        }                       //
    }
    unsigned ii = 0;
    unsigned k  = 7;
jump_rehash: ;
    do
    { // work while NULL
        ii++;
	magic_posit = (_init_hash + (ii*k)  ) % (storage->max_size); // some magic
        stored_rec = (*(storage->start_record) + magic_posit); // ???? hehe
        printf("magic=%lu look  %p \n", magic_posit, (void *)stored_rec);
    } while ((check_null_str(stored_rec->key))); // repeat while empty
    printf("%lu search %s -----looking %s\n",magic_posit,in_string,stored_rec->key);
    if (!(strcmp(stored_rec->key, in_string)))
    { // not null here!!!
        return magic_posit;
    }
    else
    { // not equal but not null!
        goto jump_rehash;
    }
}
static void copy_obj(record_storage *storage, record a_record, unsigned long position)
{
    unsigned s_len = strlen(a_record.key);
    // int s_len = snprintf(NULL,0,"{data:%c}",a_record.key);// get the size
    assert(s_len > 0);
    s_len++; // add space for null term
    char *s_tmp = calloc(sizeof(char), s_len); // allocate memory for string
    if (!(s_tmp))
    {
        printf("error memeory allocation\n");
        exit(1);
    }
    strncpy(s_tmp, a_record.key, s_len);
    s_tmp[s_len - 1] = '\0';
    record *target_record = ((*(storage->start_record) + position));
    target_record->id = a_record.id;
    target_record->value = a_record.value;
    target_record->flag = a_record.flag;
    target_record->key = s_tmp;
#ifdef DEBUG
    printf("copying done, string=%s\n", (char *)(*((*(storage->start_record) + position))).key);
#endif
}

unsigned check_position(record_storage *storage, record *a_record, unsigned long try_this_position)
{ // whether it is already occupied
    char *string_on_this_position = (*((*(storage->start_record) + try_this_position))).key;
    char *string_to_check = a_record->key;
    int rez = -1;
    if (string_on_this_position != NULL)
    {
#ifdef DEBUG
        printf("len 0 is %d, len 1 is %d \n", strlen(string_on_this_position), strlen(string_to_check));
        printf("checking string >>%s<< on posititon %lu, string to check is %s \n", string_on_this_position,
               try_this_position, string_to_check);
#endif
        rez = (strcmp(string_on_this_position, string_to_check));
    }
    else
    {
        // printf("len of input string is %d \n",strlen(string_to_check));
        rez = 1;
    }
    // printf("result of comparision is %d \n",rez);
    if (rez)
    {             // not equal,
        return 0; // go and write
    }
    else
    {             // if collision, match
        return 1; // ooccupied
    }
}
//--------------------TEST FUNCTIONS-------------------------//
//----------------------------------------------------------//
#define VVV 15
void test0()
{
    record_storage store = init_storage(20);
    char const *const some[VVV] = {
        "engl", "fransis", "fransis", "bread", "china", "no_bread", "bread", "gagagat",
        "dasd", "da",      "ttt",     "clcd",  "krf",   "русское",  "и",

    };
    for (size_t i = 0; i < VVV; ++i)
    {
        record tmp_rec = init_a_record();
        set_a_record(&tmp_rec, some[i]);
        try_append_to_storage(&store, tmp_rec);
    }
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    for (size_t i = 0; i < VVV; i++)
    {
        printf("%lu we are searching %s \n", i, some[i]);
        unsigned long getted_value = get_value_v2(&store, some[i]); // position
        printf("---\n");
        record contained = (*(*(store.start_record) + getted_value));
        printf("searched %s, found on position %lu, contains %s, meet %lu \n", some[i], getted_value, contained.key,
               contained.value);
    }
    // printout_content(&store);
    storage_destroy(&store);
}
