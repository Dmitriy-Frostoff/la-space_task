#include "../environment/arguments.h"
#include "../module_run_tasks_after_delay.h"

extern bool is_register_task;

/**
 *  @brief Register task in the @link{tasks_array[]} to delay its' usage at
 *  @link{delay} ms and get the strucure @link{PROMISE_TASK_ID} for saving
 *  registered task's id
 *
 *  @details Controller like function to get arguments and skip them further to
 *  the correspondent handler function via @link{handle_events_tasks}.
 *
 *  @note ! Impure function !
 *  - mutates the outer global variable @link{is_register_task}
 *  - implicit dependency on @callback{arguments_set_callback}
 *  - implicit dependency on @callback{arguments_set_func_arg}
 *  - implicit dependency on @callback{arguments_set_delay}
 *  - implicit dependency on @callback{handle_events_tasks}
 *
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
 *    `task` is created via `register_task` function instance of
 *    @type{Task} and nested to the @link{tasks_array}
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
 *    PROMISE_TASK_ID log_id = register_task(some_callback, 400, 400);
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
PROMISE_TASK_ID register_task(task_callback func_to_call, unsigned short arg,
                              unsigned short delay) {
  // set up the flag
  is_register_task = true;

  // update arguments
  arguments_set_callback(func_to_call);
  arguments_set_func_arg(arg);
  arguments_set_delay(delay);

  // handle the events
  return handle_events_tasks().results.result_register_task;
}
