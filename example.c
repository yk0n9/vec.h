#include <stdio.h>
#include <stdlib.h>

#include "vec.h"

typedef Vec(char) String;

String String_from(char *str)
{
    String string = Vec_new();
    while (str && *str != 0)
    {
        Vec_push(&string, *str);
        str++;
    }
    Vec_push(&string, 0);
    return string;
}

void fun(String *it)
{
    printf("%s\n", it->data);
}

void String_clean(String *it)
{
    Vec_clear(it);
}

int main()
{
    Vec(String) arr = Vec_new();

    Vec_push(&arr, String_from("123"));
    Vec_push(&arr, String_from("456"));
    Vec_push(&arr, String_from("789"));

    Vec_foreach(&arr, fun);
    // 123
    // 456
    // 789

    printf("cap = %d, len = %d\n", __capacity(&arr), Vec_len(&arr));
    // cap = 8, len = 3

    Vec_reverse(&arr);

    Vec_foreach(&arr, fun);
    // 789
    // 456
    // 123

    printf("\n");
    printf("last: %s\n", Vec_last(&arr)->data);
    // last: 123

    // free memory
    Vec_foreach(&arr, String_clean);
    Vec_clear(&arr);
}
