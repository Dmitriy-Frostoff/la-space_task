#include "./environment/global_variables.h"
#include "./module_run_tasks_after_delay.h"

/**
 *  @brief Function for delayed calling and execution with @link{arg} .
 *  Just print message. @see{register_task} for more
 *
 *  @note ! Impure function !
 *  - implicit dependency on global variable @link{task_count} from
 *    "global_variables.h"
 *
 *  @param {unsigned short} arg - delay time value (ms). Used as delay value in
 *    @link{register_task} function and in the message content.
 *
 *  @example
 *    show_task_info(400) =>
 *    OUTPUT:
 *    "Im task {1}. Create TASK with delay :{400}"
 *    => void
 *
 *    show_task_info(1800) =>
 *    OUTPUT:
 *    "Im task {2}. Create TASK with delay :{1800}"
 *    => void
 *
 */
void show_task_info(unsigned short arg) {
  printf("Im task {%hd}. Create TASK with delay :{%hd} \n", task_count, arg);
}
