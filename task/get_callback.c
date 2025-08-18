#include "./config.h"
#include "./get_callback_config.h"
#include "./global_variables.h"
#include "./utils.h"

/**
 *  @brief Get the sructure @link{PROMISE_TASK} with the last task (study the
 *  example for details!) from the @link{tasks_array[]} to call it's callback
 *  with the saved argument.
 *
 *  @note ! Impure function !
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
  // check that @link{tasks_array} is not empty
  if (task_count == 0) {
    return (PROMISE_TASK){.type = ERROR_CODE,
                          .get_callback_result.CODES_RESULT =
                              GET_CALLBACK_ARRAY_OF_TASKS_EMPTY};
  }

  // set up
  struct timespec current_ts = {};
  time_t current_timestamp_ms = 0;
  struct timespec task_created_timespec = {};
  time_t task_timestamp_ms = 0;
  unsigned short diff_timestamps_ms = 0;

  /** the task in the @link{tasks_array} with
    the least delay(ms)
    @note task_count - 1 ? => task_count - 1 == last task index in the
    @link{tasks_array} */
  Task last_task = tasks_array[task_count - 1];

  // create pure instance of @link{PROMISE_TASK} as a result value
  // (assign to it further)
  PROMISE_TASK result_promise_task = {};

  int written_var_count = timespec_get(&current_ts, TIME_UTC);

  // current_ts.tv_sec and current_ts.tv_nsec are set ? => 1(OK) (two fields are
  // set, 1 is base for @link{TIME_UTC})
  if (written_var_count == 0) {
    return (PROMISE_TASK){.type = ERROR_CODE,
                          .get_callback_result.CODES_RESULT =
                              GET_CALLBACK_TIMESPEC_GET_ERROR};
  }

  // count timestamps(ms)
  // @note with precision's loss (nsec => ms due to delay(ms))
  current_timestamp_ms =
      (time_t)(round(current_ts.tv_sec * RATIO_SEC_MS +
                     current_ts.tv_nsec / RATIO_NANOSEC_MSEC));

  task_created_timespec = (last_task).created_timespec;
  task_timestamp_ms =
      (time_t)(round(task_created_timespec.tv_sec * RATIO_SEC_MS +
                     task_created_timespec.tv_nsec / RATIO_NANOSEC_MSEC));

  diff_timestamps_ms =
      (unsigned short)(current_timestamp_ms - task_timestamp_ms);

  // check that
  // (current timestamp(count from current_ts) - Task.created_timespec) >
  //  Task.delay
  if (diff_timestamps_ms <= last_task.delay) {
    return (PROMISE_TASK){.type = ERROR_CODE,
                          .get_callback_result.CODES_RESULT =
                              GET_CALLBACK_PENDING};
  }

  // update @link{result_promise_task}
  result_promise_task =
      (PROMISE_TASK){.type = SUCCESS, .get_callback_result.TASK = last_task};

  // free the id
  PROMISE_ID_VALUE log_id_value = free_id(tasks_array[task_count - 1].id);

  switch (log_id_value.type) {
  case SUCCESS:
    break;
  case ERROR_CODE:
    return (PROMISE_TASK){.type = ERROR_CODE,
                          .get_callback_result.CODES_RESULT =
                              GET_CALLBACK_FREE_ID_ERROR};
  default:
    break;
  }

  // remove the ready task from the @link{tasks_array} (i.e. empty last task),
  // decrease quantity of tasks and return the ready task
  tasks_array[task_count - 1] = (Task){0};
  task_count -= 1;

  return result_promise_task;
}
