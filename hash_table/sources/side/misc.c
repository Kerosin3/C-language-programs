#include "misc.h"
#pragma message "including misc source"
extern void printout_content(record_storage *storage)
{
    record *t_rec = *(storage->start_record); // add index here
    size_t i = 0;
    size_t j = 0;
    printf("====================================================\n");
    while (i < storage->max_size)
    {
        if (t_rec->flag)
        { // no empty
            printf(">%5lu< | occurred:%5lu  times | word:%-35s  \n", j, t_rec->value, t_rec->key);
            j++;
        }
        else
        {
            ;
        }
        t_rec++;
        i++;
    }
    printf("========================total %lu words counted============================\n", j);
}
