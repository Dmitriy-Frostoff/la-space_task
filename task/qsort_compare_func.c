#include "./utils.h"

int qsort_compare_func(const void *num_a, const void *num_b) {
  // conversion arguments types (pointers) to @type{const  int *}
  const int *ptr_a = (const int *)num_a;
  const int *ptr_b = (const int *)num_b;

  // dereferencing values
  int a = *ptr_a;
  int b = *ptr_b;

  // sort descending
  return b - a;
}
