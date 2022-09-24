#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloca.h>
#include <limits.h>
#include "khash.h"

// shorthand way to get the key from hashtable or defVal if not found
#define kh_get_val(kname, hash, key, defVal) ({k=kh_get(kname, hash, key);(k!=kh_end(hash)?kh_val(hash,k):defVal);})

// shorthand way to set value in hash with single line command.  Returns value
// returns 0=replaced existing item, 1=bucket empty (new key), 2-adding element previously deleted
#define kh_set(kname, hash, key, val) ({int ret; k = kh_put(kname, hash,key,&ret); kh_value(hash,k) = val; ret;})

const int khStrInt = 33;
KHASH_MAP_INIT_STR(khStrInt, int) // setup khash to handle string key with int payload

int main(int argc, char *argv[])
{
    printf("hello\n");
    
   int ret, is_missing;
   khiter_t k;
   khash_t(khStrInt) *h = kh_init(khStrInt); // create a hashtable
					     //
					     //
   kh_set(khStrInt, h, "jimbo", 99);

// Retrieve the value for key "apple"
   k = kh_get(khStrInt, h, "jimbo1");  // first have to get ieter
   if (k == kh_end(h)) {  // k will be equal to kh_end if key not present
      printf("no key found for jimbo");
   } else {
      printf ("key at jimbo=%d\n", kh_val(h,k)); // next have to fetch  the actual value
   }

    return 0;
}

