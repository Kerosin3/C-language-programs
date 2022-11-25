#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SomeS
{
    int data;
    struct SomeS *next_data;
};

static const char *fmt = "%ld ";
static const char *empty = "";
static const int lost_numbers[] = {4, 8, 15, 16, 23, 42};
#define data_length sizeof(lost_numbers)/8

void print_int(int );
int conv_one(int );
struct SomeS * add_element(int , struct SomeS*);
void recur_map(struct SomeS *list, void (*mapf)(int)); // m 
struct SomeS* filter_func(struct SomeS*, int (int), struct SomeS* ); // f 
void free_memory(struct SomeS*);

int main()
{
    struct SomeS *numbers = NULL;
    struct SomeS *filtered_numbers = NULL;
    for (int i =  (((data_length*8 )/sizeof(lost_numbers[0]))-1) ; i>=0; i--)
    {
        numbers = add_element(lost_numbers[i], numbers);
    }

    recur_map(numbers, print_int);
    puts(empty);
    filtered_numbers = filter_func(numbers, conv_one, 0); // ??
    recur_map(filtered_numbers, print_int);
    puts(empty);

    free_memory(numbers);
    free_memory(filtered_numbers);
    return 0;
}


struct SomeS * add_element(int elem, struct SomeS *datalist)
{
    struct SomeS* new_Some = malloc(sizeof(struct SomeS));
    if(new_Some == NULL)
        exit(0);// finito
    new_Some->data = elem;
    new_Some->next_data = datalist;
    return new_Some;
}


struct SomeS* filter_func(struct SomeS *numbers, int (*mfunc)(int), struct SomeS* some_numbers) // f func
{
    struct SomeS *out = some_numbers;
    if(numbers == NULL)
        return out;

    if(mfunc(numbers->data) != 0)
    {
        out = add_element(numbers->data, out);
    }
    return filter_func(numbers->next_data, mfunc, out); //ff
}


int conv_one(int int_n) // p func
{
    return int_n & 1;
}


void print_int(int some_int) // use static fmt 
{
    printf(fmt, some_int);
    fflush(stdout);// !
}

void free_memory(struct SomeS *struct_data_to_free)
{ 
    if (struct_data_to_free->next_data != NULL){
	    free_memory(struct_data_to_free->next_data);
    } 
    free(struct_data_to_free); //free itself
}

void recur_map(struct SomeS *data_l, void (*mapf)(int)) // m func
{
    if(data_l == NULL)
        return;
    mapf(data_l->data);
    recur_map(data_l->next_data, mapf);
}

