#ifndef GET_CALLBACK_CONFIG_H
#define GET_CALLBACK_CONFIG_H

#include "../environment/config.h"

/**
 *  @details
 *  - GET_CALLBACK_ARRAY_OF_TASKS_EMPTY - current task counter value is 0
 *  - GET_CALLBACK_TIMESPEC_GET_ERROR - at the moment of getting current
 *    timestamp via timespec_get() function with TIME_UTC base problems occured
 *  - GET_CALLBACK_PENDING - the least task's delay is not gone yet
 *  - GET_CALLBACK_FREE_ID_ERROR - error at the process of freeing the id
 *
 */
enum Get_callback_errors_codes {
  GET_CALLBACK_ARRAY_OF_TASKS_EMPTY = 1,
  /**< current task counter value is 0 */
  GET_CALLBACK_TIMESPEC_GET_ERROR =
      2,                    /**< at the moment of getting current timestamp via
                             *    timespec_get() function with TIME_UTC base problems occured */
  GET_CALLBACK_PENDING = 3, /**< the least task's delay is not gone yet */
  GET_CALLBACK_FREE_ID_ERROR = 4, /**< error at the process of freeing the id */
};

/**
 *  @details
 *  Union for handling results of @link{get_callback} function execution.
 *  Possible values @note only one of is possible!:
 *  - TASK - @link{Task} structure, the task with delay that is gone
 *  - REGISTER_TASK_CODES - Error codes at the process of Getting the Task
 *
 */
union Union_task {
  Task TASK; /**< @link{Task} structure, the task with delay that is gone */
  enum Get_callback_errors_codes
      CODES_RESULT; /**< Error codes at the process of Getting the Task
                     */
};

/**
 *  @details
 *  Structure for handling results of @link{get_callback} function execution.
 *  - type - (SUCCESS | ERROR_CODE)
 *  - get_callback_result - union @link{union Union_task}, that is
 *    @type{Task} for TASK (SUCCESS, everything is OK) or
 *    one of error codes for ERROR_CODE
 *    i.e. (GET_CALLBACK_ARRAY_OF_TASKS_EMPTY | GET_CALLBACK_PENDING |
 *    GET_CALLBACK_FREE_ID_ERROR)
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
 *      or
 *      OUTPUT: e.g. GET_CALLBACK_FREE_ID_ERROR
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
typedef struct s_Get_callback_result {
  PROMISE_TYPE type;                    /**< SUCCESS | ERROR_CODE */
  union Union_task get_callback_result; /**< TASK | CODES_RESULT */
} PROMISE_TASK;

#endif
