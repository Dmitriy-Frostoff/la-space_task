#include "../environment/arguments.h"
#include "../module_run_tasks_after_delay.h"

extern bool is_change_task_delay;

/**
 *  @brief Modify the delay value (ms) of the task from @link{tasks_array}
 *
 *  @details Controller like function to get arguments and skip them further to
 *  the correspondent handler function via @link{handle_events_tasks}.
 *
 *  @note ! Impure function !
 *  - mutates the outer global variable @link{is_change_task_delay}
 *  - implicit dependency on @callback{arguments_set_id}
 *  - implicit dependency on @callback{arguments_set_patch_delay}
 *  - implicit dependency on @callback{handle_events_tasks}
 *
 *  - mutates the outer Task in the @link{tasks_array}
 *  - implicit dependency on @type{TASK_COUNTER}
 *  - implicit dependency on @type{PROMISE_CHANGE_TASK_DELAY}
 *  - implicit dependency on @type{Task}
 *  - implicit dependency on @type{struct timespec} of <time.h>
 *  - implicit dependency on @callback{timespec_get} function of <time.h>
 *  - implicit dependency on @callback{sort_tasks_descending_by_delay_func}
 *  - under the hood uses @link{qsort} function from <stdlib.h> for sorting
 *    descending @link{tasks_array} via Task.delay(ms)
 *
 *  @note Returns promise like structure @link{PROMISE_CHANGE_TASK_DELAY}!
 *  Examine the example below how to handle it properly!
 *
 *  @note After the moment the delay time is successfully changed, inner
 *  @link{Task.created_timespec} is newed! So previous delay(ms) is omitted.
 *
 *  @param {TASK_COUNTER} id - id of the task from @link{tasks_array} to change
 *  delay at
 *  @param {unsigned short} new_delay - new delay value (ms!)
 *
 *  @return {PROMISE_CHANGE_TASK_DELAY} - structure of complex type
 *    @see{PROMISE_CHANGE_TASK_DELAY} for details and examples below for
 *    clarification how to handle it
 *  @throw PROMISE_CHANGE_TASK_DELAY.type = ERROR_CODE
 *    - PROMISE_CHANGE_TASK_DELAY.CODES_RESULT =>
 *      - CHANGE_TASK_DELAY_ARRAY_OF_TASKS_EMPTY - current task
 *        counter value is 0
 *      - CHANGE_TASK_DELAY_TASK_ID_IS_NOT_DETERMINED - no such task
 *        with given ID
 *      - CHANGE_TASK_DELAY_TIMESPEC_GET_ERROR - at the moment of
 *        getting current timestamp via @link{timespec_get}() function with
 *        TIME_UTC base problems occured
 *
 *  @example
 *     *** Predefined context ***
 *    PROMISE_TASK_ID log_id = register_task(some_callback, 400, 400);
 *    TASK_COUNTER task_id;
 *    ***
 *    task_id = 0; (first one)
 *    ***
 *    *** Usage ***
 *    PROMISE_CHANGE_TASK_DELAY log_change_task_delay =
 *      change_task_delay(0, 1600);
 *
 *    switch (log_change_task_delay.type) {
 *    case SUCCESS:
 *      printf("log_change_task_delay: CHANGE_TASK_DELAY_DONE_SUCCESSFULLY\n");
 *      break;
 *    case ERROR_CODE:
 *      printf("ERROR_CODE: %hd\n",
 *        log_change_task_delay.CODES_RESULT);
 *      OUTPUT: e.g. CHANGE_TASK_DELAY_ARRAY_OF_TASKS_EMPTY
 *      or
 *      OUTPUT: e.g. CHANGE_TASK_DELAY_TASK_ID_IS_NOT_DETERMINED
 *      break;
 *      or
 *      OUTPUT: e.g. CHANGE_TASK_DELAY_TIMESPEC_GET_ERROR
 *      break;
 *    default:
 *      fprintf(stderr, "Error(%s() function at %d): ups... Unknown
 *        log_change_task_delay.type\n", __func__, __LINE__);
 *      break;
 *    }
 */
PROMISE_CHANGE_TASK_DELAY change_task_delay(TASK_COUNTER id,
                                            unsigned short new_delay) {
  // set up the flag
  is_change_task_delay = true;

  // update arguments
  arguments_set_id(id);
  arguments_set_patch_delay(new_delay);

  // handle the events
  return handle_events_tasks().results.result_change_task_delay;
}
