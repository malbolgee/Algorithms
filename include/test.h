#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void (*func_ord_t)(void *const a, size_t nmemb, size_t size, __compar_fn_t compar);

typedef struct _func
{

    func_ord_t f;
    char *func_name;

} func_obj_t;

#define TEST_SET 5

int un_arrays[][TEST_SET] = {{2, 6, 9, 7, 0}, {18, 20, 6, 3, 5}, {10, 20, 8, 9, 100}, {3, 6, 4, 8, 0}, {70, 200, 700, 15, 700}};
int ord_arrays[][TEST_SET] = {{0, 2, 6, 7, 9}, {3, 5, 6, 18, 20}, {8, 9, 10, 20, 100}, {0, 3, 4, 6, 8}, {15, 70, 200, 700, 700}};

int compar(const void *a, const void *b);

extern inline bool is_ord(void *const b1, size_t nmemb, size_t size, __compar_fn_t compar)
{

    char *base_ptr = (char *)b1;
    for (size_t i = 0; i < nmemb - 1; ++i)
        if (compar(&base_ptr[size * (i + 1)], &base_ptr[size * i]) > 0)
            return false;

    return true;
}

extern inline bool is_same(void *const b1, void *const b2, size_t nmemb, size_t size, __compar_fn_t compar)
{

    char *base1_ptr = (char *)b1;
    char *base2_ptr = (char *)b2;

    for (size_t i = 0; i < nmemb; ++i)
        if (compar(&base1_ptr[size * i], &base2_ptr[size * i]) == 0)
            return false;

    return true;
}

#endif