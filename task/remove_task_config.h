#ifndef REMOVE_TASK_H
#define REMOVE_TASK_H

#include "./config.h"

/**
 *  @details
 *  - REMOVE_TASK_DONE_SUCCESSFULLY - no errors, the task's delay changed
 *    succesfully
 *  - REMOVE_TASK_ARRAY_OF_TASKS_EMPTY - current task counter value is 0
 *  - REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED - no such task with given ID
 *  - REMOVE_TASK_FREE_ID_ERROR - error at the process of freeing the id
 *
 */
enum Remove_task_errors_codes {
  REMOVE_TASK_DONE_SUCCESSFULLY = 0,    /**< no errors, the task was removed
                                         *   successfully */
  REMOVE_TASK_ARRAY_OF_TASKS_EMPTY = 1, /**< current task counter value is 0 */
  REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED = 2, /**< no such task with given ID */
  REMOVE_TASK_FREE_ID_ERROR = 3, /**< error at the process of freeing the id */
};

/**
 *  @details
 *  Structure for handling results of @link{remove_task} function
 *  execution.
 *  - type - (SUCCESS | ERROR_CODE)
 *  - CODES_RESULT - enum @link{enum Remove_task_errors_codes}, that is
 *    one of error codes for ERROR_CODE
 *    ( @note CODES_RESULT with REMOVE_TASK_DONE_SUCCESSFULLY is only for
 *    SUCCESS for unification with other PROMISE_* like structures)
 *    i.e. (REMOVE_TASK_ARRAY_OF_TASKS_EMPTY |
 *    REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED | REMOVE_TASK_FREE_ID_ERROR)
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
 *      break;
 *    case ERROR_CODE:
 *      printf("ERROR_CODE: %hd\n",
 *        log_remove_task.CODES_RESULT);
 *      OUTPUT: e.g. REMOVE_TASK_ARRAY_OF_TASKS_EMPTY
 *      or
 *      OUTPUT: e.g. REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED
 *      or
 *      OUTPUT: e.g. REMOVE_TASK_FREE_ID_ERROR
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
typedef struct s_Remove_task_result {
  PROMISE_TYPE type; /**< SUCCESS | ERROR_CODE */
  enum Remove_task_errors_codes
      CODES_RESULT; /**< REMOVE_TASK_DONE_SUCCESSFULLY |
                       REMOVE_TASK_ARRAY_OF_TASKS_EMPTY |
                       REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED |
                       REMOVE_TASK_FREE_ID_ERROR */
} PROMISE_REMOVE_TASK;

#endif
