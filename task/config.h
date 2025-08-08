#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum global_variables { MAX_TASK_QUANTITY = 50 };

/**
 *  @details
 *  - @type{unsigned short} TASK_ID - type for id for the Task instance
 *
 */
typedef unsigned short TASK_ID; /**< type for id for the Task instance */

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
 *
 */
typedef struct task_template {
  task_callback callback;  /**< callback to call after delay time is gone */
  unsigned short func_arg; /**< argument to call @link{callback} with */
  unsigned short
      delay;  /**< delay time (ms) to freeze @link{callback} calling */
  TASK_ID id; /**< id of the current Task (set up at the creating moment
                 manually!) */
  unsigned short
      created_timestamp; /**< timestamp of the Task instance creating */
} Task;

/**
 *  @brief Callback type for sorting function via qsort of <stdlib.h>
 *  e.g. see{qsort_compare_func}
 *
 */
typedef int (*qsort_compare_callback)(const void *num_a, const void *num_b);

/** Global counter for id range [0:50) */
TASK_ID task_id_count = 0;
/** Quantity of the ready task (i.e. when delay time is gone) range [0:50) */
TASK_ID prepared_tasks_count = 0;

#endif
