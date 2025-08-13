#include "./config.h"
#include "./global_variables.h"
#include "./remove_task_config.h"
#include "./utils.h"

/**
 *  @brief
 *
 *
 *  @note ! Impure function !
 *  - mutates the outer @link{tasks_array}
 *  - implicit dependency on @type{TASK_COUNTER}
 *  - implicit dependency on @type{PROMISE_REMOVE_TASK}
 *  - implicit dependency on @type{Task}
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
  // check that @link{tasks_array} is not empty
  if (task_count == 0) {
    return (PROMISE_REMOVE_TASK){
        .type = ERROR_CODE, .CODES_RESULT = REMOVE_TASK_ARRAY_OF_TASKS_EMPTY};
  }

  // check, that @link{id} is in range [0; task_count - 1]
  // @note task_count - 1 ? => task id ( @link{Task tasks_array[]} index) ==
  // task_count - 1
  // id @type{unsigned short} may not be negative! so -1 => 65536 - 1 = 65535
  //  where 2 ** 16 (i.e. 2 * 8 i.e. 2 bytes = 16) = 65536
  if (id >= task_count) {
    return (PROMISE_REMOVE_TASK){.type = ERROR_CODE,
                                 .CODES_RESULT =
                                     REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED};
  }

  // get the task over @link{id} and remove the task (make it 0 zero struct
  //  i.e. to (Task){0} )
  for (TASK_COUNTER i = 0; i < task_count; i += 1) {
    // use bidirectional search
    // search from the beginning
    if (tasks_array[i].id == id) {
      // remove the Task => swap Task to (Task){0}
      tasks_array[i] = (Task){0};

      // sort @link{tasks_array} only if:
      // - more than one task in it
      if (task_count > 1) {
        // sort @link{tasks_array} descending via Task.delay (ms)
        sort_tasks_descending_by_delay(tasks_array, MAX_TASK_QUANTITY,
                                       task_count);
      }

      // update @link{task_count}
      task_count -= 1;

      return (PROMISE_REMOVE_TASK){
          .type = SUCCESS, .CODES_RESULT = REMOVE_TASK_DONE_SUCCESSFULLY};
    }

    // search from the end
    if (tasks_array[task_count - 1 - i].id == id) {
      // remove the Task => swap Task to (Task){0}
      tasks_array[task_count - 1 - i] = (Task){0};

      // sort @link{tasks_array} only if:
      // - more than one task in it
      if (task_count > 1) {
        // sort @link{tasks_array} descending via Task.delay (ms)
        sort_tasks_descending_by_delay(tasks_array, MAX_TASK_QUANTITY,
                                       task_count);
      }

      // update @link{task_count}
      task_count -= 1;

      return (PROMISE_REMOVE_TASK){
          .type = SUCCESS, .CODES_RESULT = REMOVE_TASK_DONE_SUCCESSFULLY};
    }
  }

  // handle case when no match over @link{id} happened
  return (PROMISE_REMOVE_TASK){.type = ERROR_CODE,
                               .CODES_RESULT =
                                   REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED};
}
