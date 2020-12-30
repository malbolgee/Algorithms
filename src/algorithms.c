#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/algorithms.h"

/** Byte-wise assign item of size SIZE. */
#define ASSIGN(a, b, size)           \
    do                               \
    {                                \
        size_t __size = (size);      \
        char *__a = (a), *__b = (b); \
        do                           \
        {                            \
            *__a++ = *__b++;         \
        } while (--__size > 0);      \
    } while (0)

/** Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)             \
    do                               \
    {                                \
        size_t __size = (size);      \
        char *__a = (a), *__b = (b); \
        do                           \
        {                            \
            char __tmp = *__a;       \
            *__a++ = *__b;           \
            *__b++ = __tmp;          \
        } while (--__size > 0);      \
    } while (0)

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

void insertion_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar)
{

    int j = 0;
    void *key = malloc(size);
    char *base_ptr = (char *)base;
    for (size_t i = 1; i < nmemb; ++i)
    {
        j = i - 1UL;
        ASSIGN(key, &base_ptr[i * size], size);
        while (j >= 0 && compar(key, &base_ptr[j * size]) > 0)
        {
            ASSIGN(&base_ptr[size * (j + 1)], &base_ptr[j * size], size);
            --j;
        }

        ASSIGN(&base_ptr[size * (j + 1)], key, size);
    }

    free(key);
}

void selection_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar)
{

    void *min_idx = NULL;
    char *base_ptr = (char *)base;
    for (size_t i = 0; i < nmemb - 1; ++i)
    {
        min_idx = &base_ptr[i * size];
        for (size_t j = i + 1; j < nmemb; ++j)
            if (compar(&base_ptr[j * size], min_idx) > 0)
                min_idx = &base_ptr[j * size];

        SWAP(min_idx, &base_ptr[i * size], size);
    }
}

static void heapify(void *const base, size_t nmemb, int index, size_t size, __compar_fn_t compar)
{

    char *base_ptr = (char *)base;

    int largest = index;
    int l = index * 2 + 1;
    int r = index * 2 + 2;

    if (l < (int)nmemb && compar(&base_ptr[size * largest], &base_ptr[size * l]) > 0)
        largest = l;

    if (r < (int)nmemb && compar(&base_ptr[size * largest], &base_ptr[size * r]) > 0)
        largest = r;

    if (largest != index)
    {
        SWAP(&base_ptr[size * index], &base_ptr[size * largest], size);
        heapify(base_ptr, nmemb, largest, size, compar);
    }
}

void heap_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar)
{

    char *base_ptr = (char *)base;
    for (int i = nmemb / 2 - 1; i >= 0; --i)
        heapify(base_ptr, nmemb, i, size, compar);

    for (int i = nmemb - 1; i > 0; --i)
    {
        SWAP(&base_ptr[0], &base_ptr[i * size], size);
        heapify(base_ptr, i, 0, size, compar);
    }
}

static void _merge(void *const base, void *const tmp, int l, int m, int r, size_t nmemb, size_t size, __compar_fn_t compar)
{

    int i = l;
    int k = l;
    int j = m + 1;

    char *base_ptr = (char *)base;
    char *tmp_ptr = (char *)tmp;

    while (i <= m && j <= r)
    {
        if (compar(&base_ptr[size * i], &base_ptr[size * j]) > 0)
            ASSIGN(&tmp_ptr[size * k++], &base_ptr[size * i++], size);
        else
            ASSIGN(&tmp_ptr[size * k++], &base_ptr[size * j++], size);
    }

    while (i < (int)nmemb && i <= (int)m)
        ASSIGN(&tmp_ptr[size * k++], &base_ptr[size * i++], size);

    for (int i = l; i <= r; ++i)
        ASSIGN(&base_ptr[size * i], &tmp_ptr[size * i], size);
}

void merge_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar)
{

    int low = 0;
    int hi = nmemb - 1;

    void *_tmp = malloc(size * nmemb);
    memcpy(_tmp, base, size * nmemb);

    for (int m = 1; m <= hi - low; m = m * 2)
    {
        for (int i = low; i < hi; i += m * 2)
        {
            int from = i;
            int mid = i + m - 1;
            int to = min(i + m * 2 - 1, hi);
            _merge(base, _tmp, from, mid, to, nmemb, size, compar);
        }
    }

    free(_tmp);
}

void shell_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar)
{

    void *tmp = malloc(size);
    char *base_ptr = (char *)base;
    for (int gap = nmemb / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < (int)nmemb; ++i)
        {
            int j;
            ASSIGN(tmp, &base_ptr[size * i], size);
            for (j = i; j >= gap && compar(tmp, &base_ptr[size * (j - gap)]) > 0; j -= gap)
                ASSIGN(&base_ptr[size * j], &base_ptr[size * (j - gap)], size);

            ASSIGN(&base_ptr[size * j], tmp, size);
        }
    }

    free(tmp);
}

int lower_bound(void *const base, void *const key, size_t nmemb, size_t size, __compar_fn_t compar)
{

    int low = 0;
    int hi = nmemb;
    char *base_ptr = (char *)base;

    while (low < hi)
    {
        int mid = low + (hi - low) / 2;
        int comparison = compar(&base_ptr[size * mid], key);

        if (comparison >= 0)
            hi = mid;
        else
            low = mid + 1;
    }

    return low;
}

int upper_bound(void *const base, void *const key, size_t nmemb, size_t size, __compar_fn_t compar)
{

    int low = 0;
    int hi = nmemb;
    char *base_ptr = (char *)base;

    while (low < hi)
    {
        int mid = low + (hi - low) / 2;
        int comparison = compar(&base_ptr[size * mid], key);

        if (comparison <= 0)
            low = mid + 1;
        else
            hi = mid;
    }

    return low;
}

bool is_heap(void *const base, size_t nmemb, size_t size, __compar_fn_t compar)
{

    char *base_ptr = (char *)base;

    for (int i = 0; i <= (int)(nmemb - 2) / 2; ++i)
    {

        int l = i * 2 + 1;
        int r = i * 2 + 2;

        if (compar(&base_ptr[size * l], &base_ptr[size * i]) > 0)
            return false;

        if (r < (int)nmemb && compar(&base_ptr[size * r], &base_ptr[size * i]) > 0)
            return false;
    }

    return true;
}

void *unique(void *const base, size_t nmemb, size_t size, __compar_fn_t compar)
{

    char *base_ptr = (char *)base;

    size_t j = 0;
    for (size_t i = 0; i < nmemb; ++i)
        if (compar(&base_ptr[size * i], &base_ptr[size * j]) > 0)
            ASSIGN(&base_ptr[size * (++j)], &base_ptr[size * i], size);

    return (void *)&base_ptr[size * (j + 1)];
}

void *merge(void *const b1, size_t nmemb1, void *const b2, size_t nmemb2,
            void *const b3, size_t size, __compar_fn_t compar)
{

    size_t i, j, k;
    char *b1_ptr = (char *)b1;
    char *b2_ptr = (char *)b2;
    char *b3_ptr = NULL;

    if (b3 == NULL)
        b3_ptr = (char *)malloc(size * (nmemb1 + nmemb2));
    else
        b3_ptr = (char *)b3;

    i = j = k = 0;
    while (i < nmemb1 && j < nmemb2)
    {

        if (compar(&b1_ptr[size * i], &b2_ptr[size * j]) > 0)
            ASSIGN(&b3_ptr[size * k++], &b1_ptr[size * i++], size);
        else
            ASSIGN(&b3_ptr[size * k++], &b2_ptr[size * j++], size);
    }

    while (i < nmemb1)
        ASSIGN(&b3_ptr[size * k++], &b1_ptr[size * i++], size);

    while (j < nmemb2)
        ASSIGN(&b3_ptr[size * k++], &b2_ptr[size * j++], size);

    return (void *)b3_ptr;
}

void traverse(void *const base, size_t nmemb, size_t size, void (*f)(void *const arg))
{

    char *base_ptr = (char *)base;
    for (size_t i = 0; i < nmemb; ++i)
        f(&base_ptr[size * i]);
}

int linear_search(void *const base, void *const key, size_t nmemb, size_t size, __compar_fn_t compar)
{

    char *base_ptr = (char *)base;

    for (size_t i = 0; i < nmemb; ++i)
        if (compar(&base_ptr[size * i], key) > 0)
            return i;

    return -1;
}