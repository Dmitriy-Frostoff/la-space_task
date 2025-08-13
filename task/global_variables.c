#include "./config.h"

/** Global counter for Tasks. Range [0:MAX_TASK_QUANTITY],
 * @note 0 => 0 Tasks,
 * 1 => 1 Task in the @link{tasks_array} but with index 0 !
 * 2 => 2 Tasks in the @link{tasks_array} but last with index 1 !
 * */
TASK_COUNTER task_count = 0;

/** global array for @link{Task} instances collecting and handling */
Task tasks_array[MAX_TASK_QUANTITY] = {};
