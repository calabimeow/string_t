#include <stdlib.h>

#define STRING_MALLOC(size) malloc(size)
#define STRING_FREE(ptr) free(ptr)
#define STRING_T_IMPLEMENTATION
#include "string_t.h"

#include <stdio.h>

int main()
{
    string_t string = string_new("hello weirdo");
    string_t needle = string_new("lo w");

    printf("%d\n", string_find(string, needle));
    printf("%s\n", string_concat(string, needle).data);
    printf("%c\n", string_at(string, 7));
    printf("%s\n", string_to_upper(string).data);
    printf("%s\n", string_to_lower(string).data);
    printf("%s\n", string_reverse(string_to_upper(string)).data);

    string_free(&string);
    string_free(&needle);

    return 0;
}
