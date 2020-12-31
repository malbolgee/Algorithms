#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <stdlib.h>
#include <stdbool.h>

/** Sort NMEMB elements of BASE, of SIZE bytes each,
   using COMPAR to perform the comparisons.  */
void insertion_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar);

/** Sort NMEMB elements of BASE, of SIZE bytes each,
   using COMPAR to perform the comparisons.  */
void selection_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar);

/** Sort NMEMB elements of BASE, of SIZE bytes each,
   using COMPAR to perform the comparisons.  */
void heap_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar);

/** Sort NMEMB elements of BASE, of SIZE bytes each,
   using COMPAR to perform the comparisons.  */
void merge_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar);

/** Sort NMEMB elements of BASE, of SIZE bytes each,
   using COMPAR to perform the comparisons.  */
void shell_sort(void *const base, size_t nmemb, size_t size, __compar_fn_t compar);

/** 
 * Returns an index pointing to the first 
 * element in the range [base, nmemb) that is 
 * not less than (i.e. greater or equal to) key, 
 * or last if no such element is found. 
 */
int lower_bound(void *const base, void *const key, size_t nmemb, size_t size, __compar_fn_t compar);

/** 
 * Returns an index pointing to the first
 * element in the range [base, nmemb) that is 
 * greater than value, or last if no such element is found.
 */
int upper_bound(void *const base, void *const key, size_t nmemb, size_t size, __compar_fn_t compar);

/**
 * Checks if BASE containing NMEMB elements, of SIZE bytes each, 
 * is a max/min heap or not using COMPAR to perform the comparisons;
*/
bool is_heap(void *const base, size_t nmemb, size_t size, __compar_fn_t compar);

/**
 * Eliminates all except the first element from every consecutive group of 
 * equivalent elements from the range [base, nmemb) and returns a past-the-end 
 * pointer for the new logical end of the range.
*/
void *unique(void *const base, size_t nmemb, size_t size, __compar_fn_t compar);

/**
 * Removes from the array either a single element (first == last) or a range of elements
 * ([firts, last)). Using VALUE to assign a garbage value to the erased positions, since the
 * size of the array is not effectively decreased. the function returns the number
 * of elements removed.
 *  
*/
size_t erase(void *const first, void *const last, void *value, size_t size);

/**
 * Merges two sorted ranges [b1, nmemb) and [b2, nmemb2) 
 * into one sorted range beginning at b3.
*/
void *merge(void *const b1, size_t nmemb1, void *const b2, size_t nmemb2,
            void *const b3, size_t size, __compar_fn_t compar);

/**
 * Traverse BASE, which consistis of NMEMB elements of SIZE bytes each,
 * using F to perform an action.
*/
void traverse(void *const base, size_t nmemb, size_t size, void (*f)(void *const arg));

/**
 * Do a linear search for KEY in BASE, which consists of NMEMB elements
 * of SIZE bytes each, using COMPAR to perform the comparisons. 
*/
int linear_search(void *const base, void *const key, size_t nmemb, size_t size, __compar_fn_t compar);

#endif