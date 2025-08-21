#include "./arguments.h"
#include "./module_run_tasks_after_delay.h"

extern bool is_remove_task;

/**
 *  @brief Remove the task via valid id from @link{tasks_array}
 *
 *  @details Controller like function to get arguments and skip them further to
 *  the correspondent handler function via @link{handle_events_tasks}.
 *
 *  @note ! Impure function !
 *  - mutates the outer global variable @link{is_remove_task}
 *  - implicit dependency on @callback{arguments_set_id_remove}
 *  - implicit dependency on @callback{handle_events_tasks}
 *
 *  - mutates the outer @link{tasks_array}
 *  - mutates the outer (encapsulated) @link{id_storage_array}
 *  - mutates the outer (encapsulated) @link{is_first_call}
 *  - mutates the outer (encapsulated) @link{ptr_free_elem}
 *  - implicit dependency on @type{TASK_COUNTER}
 *  - implicit dependency on @type{PROMISE_REMOVE_TASK}
 *  - implicit dependency on @type{Task}
 *  - implicit dependency on @type{ID_LIST_ELEM}
 *  - implicit dependency on @callback{free_id}
 *  - implicit dependency on @callback{sort_tasks_descending_by_delay_func}
 *  - under the hood uses @link{qsort} function from <stdlib.h> for sorting
 *    descending @link{tasks_array} via Task.delay(ms)
 *
 *  @note Returns promise like structure @link{PROMISE_REMOVE_TASK}!
 *  Examine the example below how to handle it properly!
 *
 *  @param {TASK_COUNTER} id - id of the task from @link{tasks_array} that will
 *  be removed
 *
 *  @return {PROMISE_REMOVE_TASK} - structure of complex type
 *    @see{PROMISE_REMOVE_TASK} for details and examples below for
 *    clarification how to handle it
 *  @throw PROMISE_REMOVE_TASK.type = ERROR_CODE
 *    - PROMISE_REMOVE_TASK.CODES_RESULT =>
 *      - REMOVE_TASK_ARRAY_OF_TASKS_EMPTY - current task
 *        counter value is 0
 *      - REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED - no such task
 *        with given ID
 *
 *  @example
 *    *** Predefined context ***
 *    PROMISE_TASK_ID log_id = register_task(some_callback, 400, 400);
 *    TASK_COUNTER task_id;
 *    ***
 *    task_id = 0; (first one)
 *    ***
 *    *** Usage ***
 *    PROMISE_REMOVE_TASK log_remove_task = remove_task(0);
 *
 *    switch (log_remove_task.type) {
 *    case SUCCESS:
 *      printf("log_remove_task: REMOVE_TASK_DONE_SUCCESSFULLY\n");
 *      break;
 *    case ERROR_CODE:
 *      printf("ERROR_CODE: %hd\n",
 *        log_remove_task.CODES_RESULT);
 *      OUTPUT: e.g. REMOVE_TASK_ARRAY_OF_TASKS_EMPTY
 *      or
 *      OUTPUT: e.g. REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED
 *      break;
 *    default:
 *      fprintf(stderr, "Error(%s() function at %d): ups... Unknown
 *        log_remove_task.type\n", __func__, __LINE__);
 *      break;
 *    }
 *
 *    tasks_array[0] = (Task){
 *      callback = 0
 *      func_arg = 0
 *      delay = 0
 *      id = 0
 *      created_timespec = {
 *        tv_sec = 0
 *        tv_nsec = 0
 *      }
 *    }
 *
 */
PROMISE_REMOVE_TASK remove_task(TASK_COUNTER id) {
  // set up the flag
  is_remove_task = true;

  // update arguments
  arguments_set_id_remove(id);

  // handle the events
  return handle_events_tasks().results.result_remove_task;
}
