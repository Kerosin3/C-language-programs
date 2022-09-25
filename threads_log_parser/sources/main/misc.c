#include "misc.h"
#include "khash.h"
#include "khash_setup.h"
#include <threads.h>

#define STORAGE_DEF_MAXSIZE 100

void test(void);
void test2(FILE *fp, FILE *);


khash_t(filemap_t)* file_map;

storage_url create_url_storage();
a_url *create_a_url(char *str);
long int append_a_url(a_url *url, storage_url *storage);
long int get_a_urlN(storage_url *storage, char *a_url_to_check);
void destroy_a_url(a_url *url);
void destroy_url_storage(storage_url *storage);
long int append_url_if_nexists(storage_url *storage, char *a_url_str);
long int append_url_if_nexistsV2(storage_url *storage, char *a_url_str); // use with find
void storage_expand(storage_url *storage, size_t extend_size);
void get_n_most_urls(storage_url *storage, size_t N);
void merge_structs(storage_url *main_storage, storage_url *a_storage);

storage_url create_url_storage()
{
    a_url **main_pointer = calloc(sizeof(a_url *), STORAGE_DEF_MAXSIZE);
    if (!main_pointer)
    {
        printf("error while memory allocation!\n");
        exit(1);
    }
    storage_url main_storage;
    main_storage.current_size = 0;
    main_storage.max_size = STORAGE_DEF_MAXSIZE;
    main_storage.root_storage = main_pointer;
    main_storage.khSerial = 1;
    main_storage.filemapx = kh_init(1);
    return main_storage;
}

void storage_expand(storage_url *storage, size_t extend_size)
{
    if (extend_size <= 0)
    {
        printf("pass next size more than 0\n");
        exit(1);
    }
    a_url **new_root = realloc(storage->root_storage, sizeof(a_url *) * ((storage->max_size) + extend_size));
    if (!new_root)
    {
        printf("error while reallocation\n");
        exit(1);
    }
    for (size_t j = storage->max_size; j < (storage->max_size + extend_size); j++)
    {
        new_root[j] = (void *)0;
    }
    storage->root_storage = new_root;
    storage->max_size += extend_size;
}

void destroy_url_storage(storage_url *storage)
{
    for (size_t i = 0; i < storage->max_size; i++)
    {
        a_url *current_url_p = ((storage->root_storage)[i]);
        if (!current_url_p)
        {
            continue;
        }
        free(current_url_p->a_str);
        free(current_url_p);
    }

    free(storage->root_storage);
}

long int append_a_url(a_url *url, storage_url *storage)
{
    if (storage->current_size == storage->max_size)
    {
        storage_expand(storage, STORAGE_DEF_MAXSIZE);
    }
    (storage->root_storage)[storage->current_size] = url;
    khiter_t k ;
    int ret;
//     printf("string is ->>>%s\n",url->a_str);
//     printf("current size is %u\n",storage->current_size);
    mtx_lock(&mtx_khash_store);
    k = kh_put(filemap_t, file_map, url->a_str, &ret); //append to hashtable new url
    kh_value(file_map,k) = storage->current_size;// assign N
    printf("append %s N:%d\n",url->a_str,kh_value(file_map, k));
    mtx_unlock(&mtx_khash_store);
    storage->current_size += 1;
    return 0;
}

a_url *create_a_url(char *str)
{
    a_url *t_url = malloc(sizeof(a_url));
    t_url->count = 1;
    size_t str_leng = strlen(str);
    char *string_str = calloc(1, str_leng + 1);
    if (!string_str)
    {
        printf("error while memory allocation!\n");
        exit(1);
    }
    strcpy(string_str, str);
    string_str[str_leng] = '\0';
    t_url->a_str = string_str;
    return t_url;
}
/*
long int append_url_if_nexists(storage_url *storage, char *a_url_str)
{
    long int N = -1;
    if ((N = get_a_urlN(storage, a_url_str)) >= 0)
        return 0; // if exists
    a_url *t_url = create_a_url(a_url_str);
    append_a_url(t_url, storage);
    return 1; // is not exists -> append!
}
*/
long int append_url_if_nexistsV2(storage_url *storage, char *a_url_str)
{
    
    
    long int N = -1;
    N = get_a_urlN(storage, a_url_str); 
    printf("--->\n");
    if (N >= 0)
    {
	printf("ADD COUNT N= %ld\n",N);
        (*(storage->root_storage)[N]).count++;
        return 0; // if exists
    }
    printf("creating  \n");
    a_url *t_url = create_a_url(a_url_str);
    append_a_url(t_url, storage);
    return 1; // is not exists -> append!
}



// search a url, if success -> get N, else -> -1;
long int get_a_urlN(storage_url *storage, char *a_url_to_check)
{
/*	
    khiter_t k;
    //mtx_lock(&mtx_khash_store);
    k = kh_get(filemap_t,file_map,a_url_to_check); //test is it present
    printf("test string: %s\n",a_url_to_check);
    if (k == kh_end(file_map)) {
	    printf("not exists\n");
    	    //mtx_unlock(&mtx_khash_store);
	    return -1 ; // not found
    } else { // exists
	    long ret =(long ) kh_value(file_map, k);
	    printf("EXISTS WITH NUM %ld\n",ret);
    	    //mtx_unlock(&mtx_khash_store);
	    return ret;
    }
*/



    for (size_t i = 0; i < storage->current_size; i++)
    {
        a_url *current_url_p = ((storage->root_storage)[i]);
        if (!current_url_p)
        {
            break;
        }
        char *current_url = (*(storage->root_storage)[i]).a_str;
        if (!(strcmp(current_url, a_url_to_check)))
        {
            return i;
        }
    }
    return -1;
   
}

void destroy_a_url(a_url *url)
{
    free(url->a_str);
    free(url);
}

void merge_structs(storage_url *main_storage, storage_url *a_storage)
{
    for (size_t index = 0; index < (a_storage->current_size); index++)
    { // work with second storage
        a_url *current_url_p = ((a_storage->root_storage)[index]);
        char *a_url_str = current_url_p->a_str;               // extract string
        unsigned long a_url_str_count = current_url_p->count; // extract N
        volatile long int N = get_a_urlN(main_storage, a_url_str);
        if (N >= 0)
        { // exists -> add count
            ((main_storage->root_storage)[N])->count += a_url_str_count;
            continue;
        }
        else
        {                                           // not exists
            a_url *t_url = create_a_url(a_url_str); // create new obj
            t_url->count = current_url_p->count;
            append_a_url(t_url, main_storage); // append
        }
    }
    destroy_url_storage(a_storage);
}
/*
 * call once!
 */
void get_10_most(storage_url *storage, int PARAM)
{
    printf("------------------------------------\n");
    if (PARAM == URL)
        printf("top 10 accessed pages\n");
    else
        printf("top 10 references requesters\n");
    for (size_t i = 0; i < 10; i++)
    {
        size_t c_cout = 0;
        size_t max_count = 0;
        size_t max_countN = 0;
        for (size_t j = 0; j < storage->current_size; j++)
        {
            c_cout = ((storage->root_storage)[j])->count;
            // a_url c_url = *((storage->root_storage)[j]);
            if (c_cout > max_count)
            {
                max_count = c_cout;
                max_countN = j;
                ((storage->root_storage)[j])->count = 0; // hmm
            }
        }
        if (PARAM == URL)
            printf("№%lu, count: %zu  url:[%s]\n", i + 1, max_count, ((storage->root_storage)[max_countN])->a_str);
        else
            printf("№%lu, count: %lu  referer:[%s] \n", i + 1, max_count, ((storage->root_storage)[max_countN])->a_str);
    }
    printf("------------------------------------\n");
}
