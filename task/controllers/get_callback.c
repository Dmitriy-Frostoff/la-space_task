#include "../module_run_tasks_after_delay.h"

extern bool is_get_callback;

/**
 *  @brief Get the sructure @link{PROMISE_TASK} with the last task (study the
 *  example for details!) from the @link{tasks_array[]} to call it's callback
 *  with the saved argument.
 *
 *  @details Controller like function to get arguments and skip them further to
 *  the correspondent handler function via @link{handle_events_tasks}.
 *
 *  @note ! Impure function !
 *  - mutates the outer global variable @link{is_get_callback}
 *  - implicit dependency on @callback{handle_events_tasks}
 *
 *  - mutates the outer @link{task_count}
 *  - mutates the outer @link{tasks_array}
 *  - mutates the outer (encapsulated) @link{id_storage_array}
 *  - mutates the outer (encapsulated) @link{is_first_call}
 *  - mutates the outer (encapsulated) @link{ptr_free_elem}
 *  - implicit dependency on @type{PROMISE_TASK}
 *  - implicit dependency on @type{Task}
 *  - implicit dependency on @type{struct timespec} of <time.h>
 *  - implicit dependency on @type{ID_LIST_ELEM}
 *  - implicit dependency on @callback{free_id}
 *  - implicit dependency on @callback{timespec_get} function of <time.h>
 *
 *  @note Returns promise like structure @link{PROMISE_TASK}! Examine the
 *  example below how to handle it properly!
 *  @note Expected @link{tasks_array} to be sorted descending via Task.delay(ms)
 *  value.
 *
 *  @param {void} - no params expected
 *
 *  @return {PROMISE_TASK} - structure of complex type
 *    @see{PROMISE_TASK} for details and examples below for clarification how
 *    to handle it
 *  @throw PROMISE_TASK.type = ERROR_CODE
 *    - PROMISE_TASK.get_callback_result.CODES_RESULT =>
 *      - GET_CALLBACK_ARRAY_OF_TASKS_EMPTY - current task counter value is 0
 *      - GET_CALLBACK_TIMESPEC_GET_ERROR - at the moment of getting current
 *        timestamp via timespec_get() function with TIME_UTC base problems
 *        occured
 *      - GET_CALLBACK_PENDING - the least task's delay is not gone yet
 *
 *  @example
 *    *** Predefined context ***
 *    PROMISE_TASK_ID log_id = register_task(some_callback, 400, 400);
 *    TASK_COUNTER task_id;
 *    ***
 *    task_id = 0; (first one)
 *    ***
 *    *** Usage ***
 *    PROMISE_TASK log_task = get_callback();
 *    Task task = {};
 *
 *    switch (log_task.type) {
 *    case SUCCESS:
 *      task = log_task.get_callback_result.TASK;
 *      task {
 *        callback: address_of_some_callback;
 *        func_arg: 400;
 *        delay:  400;
 *        id: 0;
 *        created_timespec: {
 *          tv.sec = 0;
 *          tv.nsec = 6291136;
 *        }
 *      }
 *      break;
 *    case ERROR_CODE:
 *      printf("ERROR_CODE: %hd\n",
 *        log_task.get_callback_result.CODES_RESULT);
 *      OUTPUT: e.g. GET_CALLBACK_ARRAY_OF_TASKS_EMPTY
 *      or
 *      OUTPUT: e.g. GET_CALLBACK_PENDING
 *      break;
 *    default:
 *      fprintf(stderr, "Error(%s() function at %d): ups... Unknown
 *        log_task.type\n", __func__, __LINE__);
 *      break;
 *    }
 *
 *    *** Run callback with arg ***
 *    task.callback(task.func_arg);
 *
 */
PROMISE_TASK get_callback(void) {
  // set up the flag
  is_get_callback = true;

  // handle the events
  return handle_events_tasks().results.result_get_callback;
}
