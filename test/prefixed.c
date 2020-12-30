#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/test.h"
#include "../include/logger.h"
#include "../include/algorithms.h"

int compar_ord(const void *a, const void *b);
int compar_same(const void *a, const void *b);
void test(void *const b1, void *const b2, size_t nmemb, size_t size, func_obj_t func);

#define INIT(FUNC)                    \
    {                                 \
        .f = FUNC, .func_name = #FUNC \
    }

int main()
{

    func_obj_t sorting[] = {

        INIT(insertion_sort),
        INIT(selection_sort),
        INIT(merge_sort),
        INIT(shell_sort),
        INIT(heap_sort)

    };

    for (size_t i = 0; i < TEST_SET; ++i)
        for (size_t j = 0; j < TEST_SET; ++j)
        {

            int tmp[TEST_SET];
            memcpy(tmp, un_arrays[j], sizeof(un_arrays[j][0]) * TEST_SET);
            test(tmp, ord_arrays[j], sizeof(un_arrays[j]) / sizeof(un_arrays[j][0]), sizeof(un_arrays[0][0]), sorting[i]);
        }

    return 0;
}

void test(void *const b1, void *const b2, size_t nmemb, size_t size, func_obj_t func)
{

    char *base_ptr = (char *)b1;
    putchar_unlocked('[');
    for (size_t i = 0; i < nmemb; ++i)
        printf("%3d%s", *(int *)(base_ptr + size * i), i < nmemb - 1 ? ", " : "] => ");

    func.f(b1, nmemb, size, compar_ord);

    bool status = is_same(b1, b2, nmemb, size, compar_same);

    LOG(func.func_name, status);

    if (status == FAIL)
    {
        printf(" => ");
        putchar_unlocked('[');
        for (size_t i = 0; i < nmemb; ++i)
            printf("%3d%s", *(int *)(base_ptr + size * i), i < nmemb - 1 ? ", " : "] => ");
    }

    putchar_unlocked('\n');
}

int compar_ord(const void *a, const void *b)
{

    return *(int *)a <= *(int *)b;
}

int compar_same(const void *a, const void *b)
{

    return *(int *)a == *(int *)b;
}
