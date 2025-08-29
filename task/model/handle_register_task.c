#include "../environment/global_variables.h"
#include "../utilities/utils.h"
#include "./register_task_config.h"

/**
 *  @brief Register task in the @link{tasks_array[]} to delay its' usage at
 *  @link{delay} ms and get the strucure @link{PROMISE_TASK_ID} for saving
 *  registered task's id
 *
 *  @note ! Impure function !
 *  - mutates the outer @link{task_count}
 *  - mutates the outer @link{tasks_array}
 *  - mutates the outer (encapsulated) @link{id_storage_array}
 *  - mutates the outer (encapsulated) @link{is_first_call}
 *  - mutates the outer (encapsulated) @link{ptr_free_elem}
 *  - implicit dependency on @type{PROMISE_TASK_ID}
 *  - implicit dependency on @type{task_callback}
 *  - implicit dependency on @type{Task}
 *  - implicit dependency on @type{struct timespec} of <time.h>
 *  - implicit dependency on @type{ID_LIST_ELEM}
 *  - implicit dependency on @callback{get_id}
 *  - implicit dependency on global variable @link{MIN_DELAY_FOR_SORT}
 *  - implicit dependency on @callback{timespec_get} function of <time.h>
 *  - implicit dependency on @callback{sort_tasks_descending_by_delay_func}
 *  - under the hood uses @link{qsort} function from <stdlib.h> for sorting
 *    descending @link{tasks_array} via Task.delay(ms)
 *
 *  @note Returns promise like structure @link{PROMISE_TASK_ID}! Examine the
 *  example below how to handle it properly!
 *
 *  @param {task_callback} func_to_call - callback that user will call with
 *    @link{arg} after @link{delay} ms is gone
 *    e.g. @see{show_task_info}
 *  @param {unsigned short} arg - argument to call with @link{func_to_call}
 *  @param {unsigned short} delay - delay time (ms). When it's gone user can
 *    call `func_to_call(arg)` or `Task task.callback(task.func_arg)` , where
 *    `task` is created via `handle_register_task` function instance of
 * @type{Task} and nested to the @link{tasks_array}
 *
 *  @return {PROMISE_TASK_ID} - structure of complex type
 *    @see{PROMISE_TASK_ID} for details and examples below for clarification how
 *    to handle it
 *  @throw PROMISE_TASK_ID.type = ERROR_CODE
 *    - PROMISE_TASK_ID.register_task_result.CODES_RESULT =>
 *      REGISTER_TASK_ARRAY_OF_TASKS_FULL - no free space to add extra Task
 *      REGISTER_TASK_TIMESPEC_GET_ERROR - problems occured at
 *      @link{timespec_get}() function calling
 *
 *  @example
 *    PROMISE_TASK_ID log_id = handle_register_task(some_callback, 400, 400);
 *    TASK_COUNTER task_id;
 *
 *    switch (log_id.type) {
 *    case SUCCESS:
 *      task_id = log_id.register_task_result.TASK_ID;
 *      printf("task_id: %hd\n", task_id);
 *      OUTPUT: e.g. 9 (task_id: 9)
 *      break;
 *    case ERROR_CODE:
 *      printf("ERROR_CODE: %hd\n",
 *        log_id.register_task_result.CODES_RESULT);
 *      OUTPUT: e.g. REGISTER_TASK_ARRAY_OF_TASKS_FULL
 *      or
 *      OUTPUT: e.g. REGISTER_TASK_TIMESPEC_GET_ERROR
 *      break;
 *    default:
 *      fprintf(stderr, "Error(%s() function at %d): ups... Unknown
 *        log_id.type\n", __func__, __LINE__);
 *      break;
 *    }
 *
 */
PROMISE_TASK_ID handle_register_task(task_callback func_to_call,
                                     unsigned short arg, unsigned short delay) {
  // prevent adding excessive task
  if (task_count >= MAX_TASK_QUANTITY) {
    return (PROMISE_TASK_ID){.type = ERROR_CODE,
                             .register_task_result.CODES_RESULT =
                                 REGISTER_TASK_ARRAY_OF_TASKS_FULL};
  }

  // create pure @link{Task} instance
  Task task = {};

  // create pure @link{PROMISE_TASK_ID} instance
  // (assign to it further)
  PROMISE_TASK_ID result_promise_task_id = {};

  // set up current timestamp
  struct timespec ts = {};
  int written_var_count = timespec_get(&ts, TIME_UTC);

  // ts.tv_sec and ts.tv_nsec are set ? => 1(OK) (two fields are set, 1 is base
  // for @link{TIME_UTC})
  if (written_var_count == 0) {
    return (PROMISE_TASK_ID){.type = ERROR_CODE,
                             .register_task_result.CODES_RESULT =
                                 REGISTER_TASK_TIMESPEC_GET_ERROR};
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
  PROMISE_ID_VALUE log_id_value = get_id();

  switch (log_id_value.type) {
  case SUCCESS:
    task.id = log_id_value.handle_id_result.ID_VALUE;
    break;
  case ERROR_CODE:
    return (PROMISE_TASK_ID){.type = ERROR_CODE,
                             .register_task_result.CODES_RESULT =
                                 REGISTER_TASK_GET_ID_ERROR};
    break;
  default:
    break;
  }

  // nest the task instance to the @kink{tasks_array}
  tasks_array[task_count] = task;

  // update @link{result_promise_task_id}
  result_promise_task_id = (PROMISE_TASK_ID){
      .type = SUCCESS, .register_task_result.TASK_ID = task_count};

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
    sort_tasks_descending_by_delay(tasks_array, MAX_TASK_QUANTITY, task_count);
  }

  return result_promise_task_id;
}
