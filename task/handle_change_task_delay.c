#include "./change_task_delay_config.h"
#include "./config.h"
#include "./global_variables.h"
#include "./utils.h"

/**
 *  @brief Modify the delay value (ms) of the task from @link{tasks_array}
 *
 *  @note ! Impure function !
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
 * handle_change_task_delay(0, 1600);
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
PROMISE_CHANGE_TASK_DELAY handle_change_task_delay(TASK_COUNTER id,
                                                   unsigned short new_delay) {
  // check that @link{tasks_array} is not empty
  if (task_count == 0) {
    return (PROMISE_CHANGE_TASK_DELAY){
        .type = ERROR_CODE,
        .CODES_RESULT = CHANGE_TASK_DELAY_ARRAY_OF_TASKS_EMPTY};
  }

  // check, that @link{id} is in range [0; task_count - 1]
  // @note task_count - 1 ? => task id ( @link{Task tasks_array[]} index) ==
  // task_count - 1
  // id @type{unsigned short} may not be negative! so -1 => 65536 - 1 = 65535
  //  where 2 ** 16 (i.e. 2 * 8 i.e. 2 bytes = 16) = 65536
  if (id >= task_count) {
    return (PROMISE_CHANGE_TASK_DELAY){
        .type = ERROR_CODE,
        .CODES_RESULT = CHANGE_TASK_DELAY_TASK_ID_IS_NOT_DETERMINED};
  }

  // set up current timestamp
  struct timespec ts = {};
  int written_var_count = timespec_get(&ts, TIME_UTC);

  // ts.tv_sec and ts.tv_nsec are set ? => 1(OK) (two fields are set, 1 is base
  // for @link{TIME_UTC})
  if (written_var_count == 0) {
    return (PROMISE_CHANGE_TASK_DELAY){
        .type = ERROR_CODE,
        .CODES_RESULT = CHANGE_TASK_DELAY_TIMESPEC_GET_ERROR};
  }

  // get the task over @link{id} and change the task
  for (TASK_COUNTER i = 0; i < task_count; i += 1) {
    // use bidirectional search
    // search from the beginning
    if (tasks_array[i].id == id) {
      // update the task's fields
      tasks_array[i].created_timespec = ts;
      tasks_array[i].delay = new_delay;

      // sort @link{tasks_array} only if:
      // - more than one task in it
      // - current task index > 0 and
      //   current task's delay > previous task's delay
      if ((task_count > 1) &&
          ((i > 0) && (tasks_array[i].delay > tasks_array[i - 1].delay))) {
        // sort @link{tasks_array} descending via Task.delay (ms)
        sort_tasks_descending_by_delay(tasks_array, MAX_TASK_QUANTITY,
                                       task_count);
      }

      return (PROMISE_CHANGE_TASK_DELAY){
          .type = SUCCESS, .CODES_RESULT = CHANGE_TASK_DELAY_DONE_SUCCESSFULLY};
    }

    // search from the end
    if (tasks_array[task_count - 1 - i].id == id) {
      // update the task's fields
      tasks_array[task_count - 1 - i].created_timespec = ts;
      tasks_array[task_count - 1 - i].delay = new_delay;

      // sort @link{tasks_array} only if:
      // - more than one task in it
      // - current task index > 0 and
      //   current task's delay > previous task's delay
      if ((task_count > 1) && ((task_count - 1 - i > 0) &&
                               (tasks_array[task_count - 1 - i].delay >
                                tasks_array[task_count - 2 - i].delay))) {
        // sort @link{tasks_array} descending via Task.delay (ms)
        sort_tasks_descending_by_delay(tasks_array, MAX_TASK_QUANTITY,
                                       task_count);
      }

      return (PROMISE_CHANGE_TASK_DELAY){
          .type = SUCCESS, .CODES_RESULT = CHANGE_TASK_DELAY_DONE_SUCCESSFULLY};
    }
  }

  // handle case when no match over @link{id} happened
  return (PROMISE_CHANGE_TASK_DELAY){
      .type = ERROR_CODE,
      .CODES_RESULT = CHANGE_TASK_DELAY_TASK_ID_IS_NOT_DETERMINED};
}
