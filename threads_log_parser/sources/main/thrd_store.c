#include "thrd_store.h"

atomic_llong total_bytes = 0;
mtx_t mtx_murl_storage;
mtx_t mtx_mrefer_storage;

typedef struct storage_cont
{
    storage_url *main_storage_url;
    storage_url *main_storage_refer;
    storage_url *url_storage;
    storage_url *refer_storage;
    int assoc_fd;
    mtx_t *mtx_done;
    bool flags;

} storage_cont;

void wrap_string_parse(storage_cont *g_storage)
{
    signed long long total_bytesF = parse_string(g_storage->assoc_fd, g_storage->url_storage, g_storage->refer_storage);
    total_bytes += total_bytesF; // add total

    mtx_lock(&mtx_murl_storage);
    merge_structs(g_storage->main_storage_url, g_storage->url_storage);
    mtx_unlock(&mtx_murl_storage);

    mtx_lock(&mtx_mrefer_storage);
    merge_structs(g_storage->main_storage_refer, g_storage->refer_storage);
    mtx_unlock(&mtx_mrefer_storage);

    mtx_lock(g_storage->mtx_done);
    g_storage->flags = true;
    mtx_unlock(g_storage->mtx_done);

    free((g_storage->url_storage));
    free((g_storage->refer_storage));
    free(g_storage);

    thrd_exit(1);
}

void process_data(int *fds)
{
    int n_files = 0;
    unsigned n_thrd = 0;
    while ((fds[n_files] != -1))
    {
        n_files++;
    }
    n_thrd = n_files;
    mtx_init(&mtx_mrefer_storage, mtx_plain); // init mtx
    mtx_init(&mtx_murl_storage, mtx_plain);   // init mtx

    printf("number of threads will be used: %u \n", n_thrd);
    printf("please be patient!\n");

    thrd_t threads_pool[n_thrd]; // create threads

    mtx_t mtx_flags_done[n_thrd]; // create mutexes
    bool flags[n_thrd];           // create flags

    for (size_t i = 0; i < n_thrd; i++)
    {
        mtx_init(&mtx_flags_done[i], mtx_plain); // init mutexes
        flags[i] = false;                        // int flags
    }

    storage_url main_storage_url = create_url_storage();
    storage_url main_storage_refer = create_url_storage();

    thrd_t thrd_pullze_solver; // create threads

    size_t i = 0;
    while ((fds[i] != -1))
    {
        if (fds[i] == -1)
            break;

        storage_cont *t_storage_cont = calloc(sizeof(storage_cont), 1);

        t_storage_cont->main_storage_refer = &main_storage_refer; // assign main
        t_storage_cont->main_storage_url = &main_storage_url;     // assign main

        storage_url *t_url_storage = calloc(sizeof(storage_url), 1);
        *t_url_storage = create_url_storage();

        storage_url *t_refer_storage = calloc(sizeof(storage_url), 1);
        *t_refer_storage = create_url_storage();

        if (!t_storage_cont || !t_url_storage || !t_refer_storage)
            exit(1);

        t_storage_cont->refer_storage = t_refer_storage; // assign thrd storages
        t_storage_cont->url_storage = t_url_storage;     // assign thrd storages

        t_storage_cont->assoc_fd = fds[i]; // assign fd
        t_storage_cont->mtx_done = &(mtx_flags_done[i]);
        flags[i] = false;
        t_storage_cont->flags = flags[i];

        int tc_ret = thrd_create(&threads_pool[i], (thrd_start_t)wrap_string_parse, (void *)t_storage_cont);
        if (tc_ret == thrd_error)
        {
            printf("error while %zu thread creation\n", i);
            exit(1);
        }
        i++;
    }
    for (size_t j = 0; j < n_thrd; j++)
    {
        int rez = -1;
        if (thrd_join(threads_pool[j], &rez) != thrd_success)
        {
            printf("error joining thread %lu\n", j);
        }
    }

    get_10_most(&main_storage_url, URL);
    get_10_most(&main_storage_refer, REFERERENCES);
    printf("TOTAL BYTES SENDED [%lld]\n", total_bytes);
    printf("--------------------------------------\n");

    destroy_url_storage(&main_storage_url);
    destroy_url_storage(&main_storage_refer);

//    close_all_fd(fds);
}
