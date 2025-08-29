#ifndef ARGUMENTS_CONFIG_H
#define ARGUMENTS_CONFIG_H

#include "../model/handle_events_tasks.h"
#include "./config.h"

/**
 *  @brief Structure for detailing the arguments for proper handler functions
 *  execution
 *
 *  @details
 *  - @type{task_callback} - @see{task_callback}
 *  - @type{unsigned short} func_arg - argument to call @link{task_callback}
 *    with after delay is gone
 *  - @type{unsigned short} delay - delay time (ms) to freeze @link{callback}
 *    calling
 *  - @type{unsigned short} patch_delay - updated delay time (ms) to freeze
 *    @link{callback} calling
 *  - @type{TASK_ID} id - id of the current Task instance
 *  - @type{TASK_ID} id_remove - id of the Task to be removed
 *
 */
typedef struct s_Arguments {
  task_callback callback;  /**< callback to call after delay time is gone */
  unsigned short func_arg; /**< argument to call @link{callback} with */
  unsigned short
      delay; /**< delay time (ms) to freeze @link{callback} calling */
  unsigned short patch_delay; /**< updated delay time (ms) to freeze
                                 @link{callback} calling */
  unsigned short id;          /**< id of the current Task  */
  unsigned short id_remove;   /**< id of the Task to be removed */
} Arguments;

#endif
