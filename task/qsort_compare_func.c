#include "./utils.h"

int qsort_compare_func(const void *task_a, const void *task_b) {
  // narrowing arguments types (pointers)
  const Task *ptr_a = (const Task *)task_a;
  const Task *ptr_b = (const Task *)task_b;

  // dereferencing values
  Task a = *ptr_a;
  Task b = *ptr_b;

  // sort descending
  return b.delay - a.delay;
}
