#ifndef CONFIG_H
#define CONFIG_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum global_variables {
  MAX_TASK_QUANTITY = 50,  /**< size of array for Tasks instances */
  MIN_DELAY_FOR_SORT = 50, /**< min delay to run qsort in the Tasks array */
  RATIO_SEC_MS = 1000LL,   /**< for converting sec => ms */
  RATIO_NANOSEC_MSEC = 1000000LL,  /**< for converting nsec => ms */
  RATIO_SEC_NANOSEC = 1000000000LL /**< for converting sec => ns */
};

/**
 *  @brief type for global Tasks counter
 *
 */
typedef unsigned short TASK_COUNTER; /**< type for tasks counter */

/**
 *  @brief Callback to use after delay time in the task is gone
 *  e.g. check the @see{show_task_info} for details
 *
 */
typedef void (*task_callback)(unsigned short arg);

/**
 *  @brief Structure for detailing the task entity
 *
 *  @details
 *  - @type{task_callback} - @see{task_callback}
 *  - @type{unsigned short} func_arg - argument to call @link{task_callback}
 *    with after delay is gone
 *  - @type{unsigned short} delay - delay time (ms) to freeze @link{callback}
 *    calling
 *  - @type{TASK_ID} id - id of the current Task instance
 *  - @type{struct timespec} created_timespec - timespec structure of
 *    the Task instance creating
 *    @note Before usage (!transformation due to @link{delay} measurement units
 *    (e.g. ms) expected!) do this:
 *    e.g. (Task.created_timespec.tv_sec * 1000LL +
 *      Task.created_timespec.tv_nsec / 1000000LL) or
 *    (Task.created_timespec.tv_sec * RATIO_SEC_MS +
 *      Task.created_timespec.tv_nsec / RATIO_NANOSEC_MSEC)
 *
 */
typedef struct task_template {
  task_callback callback;  /**< callback to call after delay time is gone */
  unsigned short func_arg; /**< argument to call @link{callback} with */
  unsigned short
      delay;       /**< delay time (ms) to freeze @link{callback} calling */
  TASK_COUNTER id; /**< id of the current Task (set up at the creating moment
                 manually!) */
  struct timespec created_timespec; /**< created_timespec structure of the Task
                                       instance creating */
} Task;

/**
 *  @details
 *  Possible types to show what is written in the Promise_* now
 *  - SUCCESS - Everything OK, possible to get data as a result
 *  - ERROR_CODE - Errors occured
 *
 */
typedef enum promise_common_type {
  SUCCESS = 0,   /**< Everything OK, ID as result */
  ERROR_CODE = 1 /**< Errors occured */
} PROMISE_TYPE;

#endif
