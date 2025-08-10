#include "./utils.h"

extern TASK_COUNTER task_count;
extern Task tasks_array[];

/**
 *  @brief Register task in the @link{tasks_array[]} to delay its' usage at
 *    @link{delay} ms
 *
 *  @note ! Impure function !
 *  - mutates the outer @link{task_count}
 *  - mutates the outer @link{tasks_array}
 *  - implicit dependency on @type{TASK_ID}
 *  - implicit dependency on @type{task_callback}
 *  - implicit dependency on @type{Task}
 *  - implicit dependency on @type{struct timespec} of <time.h>
 *  - implicit dependency on global variable @link{MIN_DELAY_FOR_SORT}
 *  - implicit dependency on @callback{qsort_compare_func}
 *  - implicit dependency on @callback{timespec_get} function of <time.h>
 *  - under the hood uses @link{qsort} function from <stdlib.h> for sorting
 *    descending @link{tasks_array}
 *
 *  @param {task_callback} func_to_call - callback that user will call with
 *    @link{arg} after @link{delay} ms is gone
 *    e.g. @see{show_task_info}
 *  @param {unsigned short} arg - argument to call with @link{func_to_call}
 *  @param {unsigned short} delay - delay time (ms). When it's gone user can
 *    call `func_to_call(arg)` or `Task task.callback(task.func_arg)` , where
 *    `task` is created via `register_task` function instance of @link{Task} and
 *    nested to the @link{tasks_array}
 *
 *  @return {TASK_ID} - structure of complex type with ID or with error happened
 *    details.
 *    @see{TASK_ID} for details and examples below for clarification
 *  @throw TASK_ID.type = ERROR_CODE
 *    - TASK_ID.register_task_result.REGISTER_TASK_CODES =>
 *      ARRAY_OF_TASKS_FULL - no free space to add extra Task
 *      TIMESPEC_GET_ERROR - problems occured at @link{timespec_get}() function
 *      calling
 *
 *  @example
 *    TASK_ID log_id = register_task(some_callback, 400, 400);
 *
 *    switch (log_id.type) {
 *    case ID:
 *      printf("ID: %hd", log_id.register_task_result.TASK_ID);
 *      OUTPUT: e.g. 9 (id = 9)
 *      break;
 *    case ERROR_CODE:
 *      printf("ERROR_CODE: %hd",
 *        log_id.register_task_result.REGISTER_TASK_CODES);
 *      OUTPUT: e.g. ARRAY_OF_TASKS_FULL
 *      or
 *      OUTPUT: e.g. TIMESPEC_GET_ERROR
 *      break;
 *    default:
 *      fprintf(stderr, "Error(%s() function at %d): ups... Unknown
 *        log_id.type\n", __func__, __LINE__);
 *      break;
 *    }
 *
 */
TASK_ID register_task(task_callback func_to_call, unsigned short arg,
                      unsigned short delay) {
  // prevent adding excessive task
  if (task_count >= MAX_TASK_QUANTITY) {
    return (TASK_ID){.type = ERROR_CODE,
                     .register_task_result.REGISTER_TASK_CODES =
                         ARRAY_OF_TASKS_FULL};
  }

  // create Task instance
  Task task = {};

  // set up current timestamp
  struct timespec ts = {};
  int written_var_count = timespec_get(&ts, TIME_UTC);

  // ts.tv_sec and ts.tv_nsec are set ? => 1(OK) (two fileds are set, 1 is base
  // for @link{TIME_UTC})
  if (written_var_count == 0) {
    return (TASK_ID){.type = ERROR_CODE,
                     .register_task_result.REGISTER_TASK_CODES =
                         TIMESPEC_GET_ERROR};
  }

  // set up the @link{task.created_timespec}
  task.created_timespec = ts;

  // set up the @link{callback}
  task.callback = func_to_call;

  // set up the @link{task.func_arg}
  task.func_arg = arg;

  // set up the @link{task.delay}
  task.delay = delay;

  // set up the @link{task.id}
  task.id = task_count;

  // nest the task instance to the @kink{tasks_array}
  tasks_array[task_count] = task;

  // update @link{task_count} counter
  task_count += 1;

  // sort tasks in the @link{tasks_array} descending (over the @link{Task.delay}
  // field value) i.e. the least delay has greater index
  // @note if @link{tasks_array} contains at least two tasks and the added
  // task's delay is greater than min delay for sort
  // and the added task's delay is greater than previous @link{tasks_array} 's
  // task delay
  if ((task_count > 1 && task.delay > MIN_DELAY_FOR_SORT) &&
      (tasks_array[task_count - 1].delay > tasks_array[task_count - 2].delay)) {
    qsort(tasks_array, task_count, sizeof(Task), qsort_compare_func);
  }

  return (TASK_ID){.type = ID, .register_task_result.TASK_ID = task_count};
}
