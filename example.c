#include <stdio.h>
#include <stdlib.h>

#include "vec.h"

void fun(int *i)
{
    printf("%d\n", *i);
}

int main()
{
    Vec(int) arr = Vec_new();
    Vec_push(&arr, 1);
    Vec_push(&arr, 2);
    Vec_push(&arr, 3);

    Vec_foreach(&arr, fun);
    // 1
    // 2
    // 3

    printf("cap = %d, len = %d\n", __capacity(&arr), Vec_len(&arr));
    // cap = 8, len = 3

    Vec_reverse(&arr);

    Vec_foreach(&arr, fun);
    // 3
    // 2
    // 1

    printf("%d\n", *Vec_last(&arr));
    // 1

    Vec_clear(&arr);
    // free memory
}
