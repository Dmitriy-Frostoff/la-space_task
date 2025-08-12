#ifndef REGISTER_TASK_CONFIG_H
#define REGISTER_TASK_CONFIG_H

#include "./config.h"

/**
 *  @details
 *  - REGISTER_TASK_ARRAY_OF_TASKS_FULL - current task counter value is greater
 *    than Tasks array size
 *  - REGISTER_TASK_TIMESPEC_GET_ERROR - at the moment of getting current
 *    timestamp via timespec_get() function with TIME_UTC base problems occured
 *
 */
enum register_task_errors_codes {
  REGISTER_TASK_ARRAY_OF_TASKS_FULL =
      1, /**< current task counter value is greater than Tasks array size */
  REGISTER_TASK_TIMESPEC_GET_ERROR =
      2, /**< at the moment of getting current timestamp via
          *    timespec_get() function with TIME_UTC base problems occured */
};

/**
 *  @details
 *  Union for handling results of @link{register_task} function execution.
 *  Possible values @note only one of is possible!:
 *  - TASK_ID - registered Task ID
 *  - REGISTER_TASK_CODES - Error codes at the process of Task registration
 *
 */
union union_id {
  unsigned short TASK_ID; /**< registered Task ID */
  enum register_task_errors_codes
      REGISTER_TASK_CODES; /**< Error codes at the process of Task registration
                            */
};

/**
 *  @details
 *  Structure for handling results of @link{register_task} function execution.
 *  - type - (SUCCESS | ERROR_CODE)
 *  - register_task_result - union @link{union union_id}, that is
 *    @type{unsigned short} for TASK_ID (SUCCESS, everything is OK) or
 *    one of error codes for ERROR_CODE
 *    i.e. (REGISTER_TASK_ARRAY_OF_TASKS_FULL |
 * REGISTER_TASK_TIMESPEC_GET_ERROR)
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
 *        log_id.register_task_result.REGISTER_TASK_CODES);
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
typedef struct register_task_result {
  PROMISE_TYPE type;                   /**< SUCCESS | ERROR_CODE */
  union union_id register_task_result; /**< TASK_ID | REGISTER_TASK_CODES */
} PROMISE_TASK_ID;

#endif
