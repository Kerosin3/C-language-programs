#include "test.h"

void test()
{
    storage_url m_storage = create_url_storage();
    srand((long)time(0)); // define a seed for the random number generator
    for (size_t k = 0; k < 3560; k++)
    {
        const char ALLOWED[] = "abcdefghijklmnopqrstuvwxyz1234567890";
        char random[10 + 1];
        int i = 0;
        int c = 0;
        int nbAllowed = sizeof(ALLOWED) - 1;
        for (i = 0; i < 10; i++)
        {
            c = rand() % nbAllowed;
            random[i] = ALLOWED[c];
        }
        random[10] = '\0';
        long int ret = append_url_if_nexists(&m_storage, random);
        printf("string is %s, ret is %ld \n", random, ret);
    }
    destroy_url_storage(&m_storage);
}

void test2(int fp, int fp2)
{
    storage_url m_storage = create_url_storage(); // url
    storage_url s_storage = create_url_storage(); // url

    storage_url mref_storage = create_url_storage(); // ref
    storage_url sref_storage = create_url_storage(); // ref

    parse_string(fp, &m_storage, &mref_storage);
    printf("storage main size %u \n", m_storage.current_size);
    printf("storage main ref size %u \n", mref_storage.current_size);

    parse_string(fp2, &s_storage, &sref_storage);
    printf("storage s size %u \n", s_storage.current_size);
    printf("storage s size %u \n", sref_storage.current_size);

    merge_structs(&m_storage, &s_storage);
    merge_structs(&mref_storage, &sref_storage);

    destroy_url_storage(&m_storage);    // free main url
    destroy_url_storage(&mref_storage); // free m  refer
}

void test3(int fp, int fp2, int fp3)
{
    signed long long total_bytes = 0;
    storage_url m_storage = create_url_storage();  // url
    storage_url s_storage = create_url_storage();  // url
    storage_url ss_storage = create_url_storage(); // url

    storage_url mref_storage = create_url_storage();  // ref
    storage_url sref_storage = create_url_storage();  // ref
    storage_url ssref_storage = create_url_storage(); // ref

    total_bytes += parse_string(fp, &m_storage, &mref_storage);
    printf("storage main size %u \n", m_storage.current_size);
    printf("storage main ref size %u \n", mref_storage.current_size);

    printf("bytes sended >>>%lld<<<\n", total_bytes);

    total_bytes += parse_string(fp2, &s_storage, &sref_storage);
    printf("storage s size %u \n", s_storage.current_size);
    printf("storage s ref size %u \n", sref_storage.current_size);

    printf("bytes sended >>>%lld<<<\n", total_bytes);

    total_bytes += parse_string(fp3, &ss_storage, &ssref_storage);
    printf("storage ss size %u \n", ss_storage.current_size);
    printf("storage ss ref size %u \n", ssref_storage.current_size);

    printf("bytes sended >>>%lld<<<\n", total_bytes);

    merge_structs(&m_storage, &s_storage);  // merget urls
    merge_structs(&m_storage, &ss_storage); // merget urls

    merge_structs(&mref_storage, &sref_storage); // merge refers
    merge_structs(&mref_storage, &ssref_storage);

    printf("storage main size after merge %u \n", m_storage.current_size);
    printf("storage main ref after merge size %u \n", mref_storage.current_size);

    get_10_most(&m_storage, URL);
    get_10_most(&mref_storage, REFERERENCES);
    printf("total bytes sended >>>%lld<<<\n", total_bytes);
    destroy_url_storage(&m_storage);    // free main url
    destroy_url_storage(&mref_storage); // free m  refer
}
