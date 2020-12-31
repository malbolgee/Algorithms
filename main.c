#include <stdio.h>
#include "./include/algorithms.h"

void print_int(void *const arg);
void print_string(void *const arg);

int compar_int(const void *a, const void *b);

int main()
{

    int v1[] = {15, 8, 20, 7, 5, 9, 13, 5};
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

    int v2[] = {19, 0, 1, 8, 10, 14, 3, 10};
    size_t n2 = sizeof(v2) / sizeof(v2[0]);

    puts("\nSecond Array:");
    traverse(v2, n2, sizeof(v2[0]), print_int);
    insertion_sort(v2, n2, sizeof(v2[0]), compar_int);
    putchar_unlocked('\n');
    traverse(v2, n2, sizeof(v2[0]), print_int);

    int v12[n1 + n2];

    // takes two (sorted) arrays and merge them, using compar to perform the comparisons
    merge(v1, n1, v2, n2, v12, sizeof(v1[0]), compar_int);
    puts("\nMerged arrays:");
    traverse(v12, n1 + n2, sizeof(v12[0]), print_int);

    int x = 10;
    int index = upper_bound(v12, &x, n1 + n2, sizeof(v12[0]), compar_int);
    printf("\nUpper Bound Index: %d\n", index);

    index = lower_bound(v12, &x, n1 + n2, sizeof(v12[0]), compar_int);
    printf("Lower Bound Index: %d\n", index);

    // The unique function returns a past-the-end pointer to the new 
    // logical end of the array (after removing the duplicates).
    // of course its better used after the array is sorted, since
    // it removes only the adjacent duplicates.
    void *last = unique(v12, n1 + n2, sizeof(v12[0]), compar_int);

    // Exemple of the erase function.
    int value = 0;

    // The erase function will receive a pointer to the beginning of a range and
    // a pointer to the end of that range. The function will remove everything
    // in between. The range could be first == last, effectively
    // removing a position rather than a range.
    // A value must be provided and will be assigned to the removed positions
    // to signal a garbage value. This is necessary since the removal of the elements
    // does not decrease the array's orignal size.
    size_t e = erase(last, &v12[n1 + n2 - 1], &value, sizeof(v12[0]));
    traverse(v12, (n1 + n2) - e, sizeof(v1[0]), print_int);

    printf("\nAmount of elements removed:: %lu\n", e);

    return 0;
}

int compar_int(const void *a, const void *b)
{

    return *(int *)a - *(int *)b;
}

void print_int(void *const arg)
{

    printf("%d ", *(int *)arg);
}

void print_string(void *const arg)
{

    printf("%s\n", (char *)arg);
}