#include <stdio.h>
#include "./include/algorithms.h"

void print_int(void *const arg);
void print_string(void *const arg);

int compar_int(const void *a, const void *b);

int main()
{

    int v1[] = {15, 8, 20, 7, 5, 9, 13};
    size_t n1 = sizeof(v1) / sizeof(v1[0]);

    // Function to traverse an array and perform an action uppon each element.
    // In this case, i'm just printing each element from the original array.
    puts("First Array:");
    traverse(v1, n1, sizeof(v1[0]), print_int);

    // MergeSort sorts the array using a function to perform the comparison between
    // each element.
    merge_sort(v1, n1, sizeof(v1[0]), compar_int);

    putchar_unlocked('\n');
    // Printing the sorted array.
    traverse(v1, n1, sizeof(v1[0]), print_int);

    int v2[] = {19, 0, 1, 8, 10, 14, 3};
    size_t n2 = sizeof(v2) / sizeof(v2[0]);

    puts("\nSecond Array:");
    traverse(v2, n2, sizeof(v2[0]), print_int);
    insertion_sort(v2, n2, sizeof(v2[0]), compar_int);
    putchar_unlocked('\n');
    traverse(v2, n2, sizeof(v2[0]), print_int);

    int v12[n1 + n2];

    // takes two arrays and merge them, using compar
    merge(v1, n1, v2, n2, v12, sizeof(v1[0]), compar_int);
    puts("\nMerged arrays:");
    traverse(v12, n1 + n2, sizeof(v12[0]), print_int);

    return 0;
}

int compar_int(const void *a, const void *b)
{

    return *(int *)a <= *(int *)b;
}

void print_int(void *const arg)
{

    printf("%d ", *(int *)arg);
}

void print_string(void *const arg)
{

    printf("%s\n", (char *)arg);
}