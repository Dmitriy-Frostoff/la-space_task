#ifndef CHANGE_TASK_DELAY_CONFIG_H
#define CHANGE_TASK_DELAY_CONFIG_H

#include "./config.h"

/**
 *  @details
 *  - CHANGE_TASK_DELAY_DONE_SUCCESSFULLY - no errors, the task's delay changed
 *    succesfully
 *  - CHANGE_TASK_DELAY_ARRAY_OF_TASKS_EMPTY - current task counter value is 0
 *  - CHANGE_TASK_DELAY_TASK_ID_IS_NOT_DETERMINED - no such task with given ID
 *  - CHANGE_TASK_DELAY_TIMESPEC_GET_ERROR - at the moment of getting current
 *    timestamp via timespec_get() function with TIME_UTC base problems occured
 *
 */
enum Change_task_delay_errors_codes {
  CHANGE_TASK_DELAY_DONE_SUCCESSFULLY = 0, /**< no errors, the task's delay
                                            * changed succesfully */
  CHANGE_TASK_DELAY_ARRAY_OF_TASKS_EMPTY =
      1, /**< current task counter value is 0 */
  CHANGE_TASK_DELAY_TASK_ID_IS_NOT_DETERMINED =
      2, /**< no such task with given ID */
  CHANGE_TASK_DELAY_TIMESPEC_GET_ERROR =
      3, /**< at the moment of getting current
          *    timestamp via timespec_get() function with TIME_UTC base problems
          * occured */
};

/**
 *  @details
 *  Structure for handling results of @link{change_task_delay} function
 *  execution.
 *  - type - (SUCCESS | ERROR_CODE)
 *  - CODES_RESULT - enum @link{enum Change_task_delay_errors_codes}, that is
 *    one of error codes for ERROR_CODE
 *    ( @note CODES_RESULT with CHANGE_TASK_DELAY_DONE_SUCCESSFULLY is only for
 *    SUCCESS for unification with other PROMISE_* like structures)
 *    i.e. (CHANGE_TASK_DELAY_ARRAY_OF_TASKS_EMPTY |
 *    CHANGE_TASK_DELAY_TASK_ID_IS_NOT_DETERMINED |
 *    CHANGE_TASK_DELAY_TIMESPEC_GET_ERROR)
 *
 *  @example
 *    *** Predefined context ***
 *    PROMISE_TASK_ID log_id = register_task(some_callback, 400, 400);
 *    TASK_COUNTER task_id;
 *    ***
 *    task_id = 0; (first one)
 *    ***
 *    *** Usage ***
 *    PROMISE_CHANGE_TASK_DELAY log_change_task_delay = change_task_delay(0,
 *      1600);
 *
 *    switch (log_change_task_delay.type) {
 *    case SUCCESS:
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
 *
 */
typedef struct s_Change_task_delay_result {
  PROMISE_TYPE type; /**< SUCCESS | ERROR_CODE */
  enum Change_task_delay_errors_codes
      CODES_RESULT; /**< CHANGE_TASK_DELAY_DONE_SUCCESSFULLY |
                       CHANGE_TASK_DELAY_ARRAY_OF_TASKS_EMPTY |
                       CHANGE_TASK_DELAY_TASK_ID_IS_NOT_DETERMINED |
                       CHANGE_TASK_DELAY_TIMESPEC_GET_ERROR */
} PROMISE_CHANGE_TASK_DELAY;

#endif
