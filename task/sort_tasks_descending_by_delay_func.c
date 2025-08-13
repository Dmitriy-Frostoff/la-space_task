#include "./utils.h"

/**
 *  @brief Callback for @link{qsort} function of <stdlib.h>
 *
 *  Sort descending Tasks via @link{Task.delay}(ms)
 *
 *  @note ! Impure function !
 *  - implicit dependency on @type{Task}
 *
 *  @param {const void *} task_a - pointer to the task
 *  @param {const void *} task_b - pointer to the task
 *
 *  @return {-1} - stands for => task_a.delay < task_b.delay
 *  so in descending order will be {task_b, task_a}
 *  @return {0} - stands for => task_a.delay == task_b.delay
 *  so in descending order will be {task_a, task_b}
 *  @return {1} - stands for => task_a.delay > task_b.delay
 *  so in descending order will be {task_a, task_b}
 *
 */
static int qsort_compare_func(const void *task_a, const void *task_b) {
  // narrowing arguments types (pointers)
  const Task *ptr_a = (const Task *)task_a;
  const Task *ptr_b = (const Task *)task_b;

  // dereferencing values
  Task a = *ptr_a;
  Task b = *ptr_b;

  // sort descending
  return b.delay - a.delay;
}

/**
 *  @brief Sort array of tasks ( of @type{Task} ) descending by delay(ms) (
 *  @link{Task.delay} )
 *
 *  @note ! Impure function !
 *  - mutates the outer @link{arr[]}
 *  - implicit dependency on @type{Task}
 *  - implicit dependency on @callback{qsort_compare_func} (but it's
 *    incapsulated in the module)
 *
 *  @note Set only *desired* @link{elems_quantity_to_sort} (i.e. indexes will be
 *  in range [0; @link{elems_quantity_to_sort}] ) to prevent unnecessary
 *  @link{arr} sorts and resources usage.
 *
 *  @param {Task []} arr - array of @type{Task} 's to sort
 *  @param {unsigned short} elems_quantity_to_sort - quantity of elems to sort
 *  @note Possible value must be not greater than @link{arr} size! But can be
 *  less, so only *the given quantity of elems* will be sorted
 *
 *  @example
 *    Task arr[3] = {
 *      (Task){
 *        func_arg = 400
 *        delay = 400
 *        id = 0
 *        created_timespec{...}
 *      },
 *      (Task){
 *        func_arg = 960
 *        delay = 960
 *        id = 2
 *        created_timespec{...}
 *      },
 *      (Task){
 *        func_arg = 1400
 *        delay = 1400
 *        id = 1
 *        created_timespec{...}
 *      }
 *    }
 *
 *    sort_tasks_descending_by_delay(arr, 3) => void
 *    arr{
 *      (Task){
 *        func_arg = 1400
 *        delay = 1400
 *        id = 1
 *        created_timespec{...}
 *      },
 *      (Task){
 *        func_arg = 960
 *        delay = 960
 *        id = 2
 *        created_timespec{...}
 *      },
 *      (Task){
 *        func_arg = 400
 *        delay = 400
 *        id = 0
 *        created_timespec{...}
 *      },
 *    }
 *
 */
void sort_tasks_descending_by_delay(Task arr[], const size_t ARR_SIZE,
                                    unsigned short elems_quantity_to_sort) {
  // check that @link{elems_quantity_to_sort} is not greater than given arr size
  if (elems_quantity_to_sort > ARR_SIZE) {
    elems_quantity_to_sort = ARR_SIZE;
  }

  qsort(arr, elems_quantity_to_sort, sizeof(Task), qsort_compare_func);
}
