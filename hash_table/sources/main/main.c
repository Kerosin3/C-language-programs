#include "hash_f.h"
#include "misc.h"
//#define DEBUG

typedef struct
{
    long int begin;
    long int end;
    char *word;
} word_pointers;

word_pointers find_a_word(FILE *fp);

void *extract_a_word(word_pointers);
unsigned END_REACHED = 0;

int main(int argc, char *argv[])
{
    if (argc > 2) {
	printf("please specify just a filename, exiting..");
	exit(1);
    }
    FILE *fp_r;
    if ((fp_r = fopen(argv[1], "rb")) == NULL)
    {
        printf("error opening file, aborting...\n");
        exit(1);
    }
    rewind(fp_r);
    word_pointers some_word;
    record_storage store = init_storage(10000); // init storage
    unsigned long counter = 0;
    while (((some_word = find_a_word(fp_r)).word))
    { // WHILE NOT NULL
        if (some_word.begin == some_word.end)
            continue; // if ???? zero length
#ifdef DEBUG
        printf("--->your word is \"%s\"\n", (char *)(some_word.word));
#endif
        counter++;
        record tmp_rec = init_a_record();
        set_a_record(&tmp_rec, (const char *)some_word.word);
        append_to_storage(&store, tmp_rec);
        //calc_hash((char *)(some_word.word)); // memory is assigned here
        free(some_word.word);
    }
    printf("processed total %lu words in the text file\n", counter);
    //printout_content(&store);
#ifdef DEBUG
    //test0();
#endif
    fclose(fp_r);
    storage_destroy(&store);
    //test0();
    (void)argc;
    return 0;
}

word_pointers find_a_word(FILE *fp)
{
    uint8_t read_char = 0;
    long int beg = 0;
    long int end = 0;
    beg = ftell(fp); // set beginning to current position
    word_pointers out;
    out.begin = beg;
    unsigned i = 0;
    do
    {
        if (feof(fp))
        {
            end = ftell(fp);
            out.end = end;
            END_REACHED = 1;
            out.word = NULL;
            return out;
        }
        fread(&read_char, 1, 1, fp); // read one byte and move cursor
        i++;
    } while (!(isspace(read_char))); // not space or EOF
    i = i - 1;                       // decrement last i, i+1 == total elements need
    char *a_word = calloc(i + 1, sizeof(char)); // one for NULL TERMINATOR
    if (!(a_word))
    {
        printf("ERROR WHILE ASSIGNING WORD, WHAT IS ITS LENGTH???\n");
        exit(1);
    }
    char *ptr_a_word = a_word;
    signed convert = ~i;          // convert = (-i + 1) ONE CHAR MORE
    fseek(fp, convert, SEEK_CUR); // set cursor back
    for (size_t j = 0; j < i; ++j)
    {                                // read content 0.1.2..6
        fread(&read_char, 1, 1, fp); // read one byte
        ptr_a_word[j] = read_char;
    }
    ptr_a_word[i] = '\0'; // set null symbol
    end = ftell(fp);
    out.end = end;
    // int width = 0;
    // width = end - beg; // no need to add extra for null
    a_word = (END_REACHED) ? (void *)0 : a_word; // i size is ok
    out.word = a_word;
    do
    { // skip whitepaces
        fread(&read_char, 1, 1, fp);
    } while (!(isspace(read_char)));
    return out;
}
