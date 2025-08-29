#ifndef HANDLE_EVENTS_TASKS_CONFIG_H
#define HANDLE_EVENTS_TASKS_CONFIG_H

#include "../environment/config.h"
#include "./change_task_delay_config.h"
#include "./get_callback_config.h"
#include "./register_task_config.h"
#include "./remove_task_config.h"

/**
 *  @details
 *  - RESULT_UNKNOWN - undefined flag, no match with the controller function
 *    calls
 *  - RESULT_REGISTER_TASK - result flag with the appropriate type for the
 *    register_task controller - like function
 *  - RESULT_GET_CALLBACK - result flag with the appropriate type for the
 *    get_callback controller - like function
 *  - RESULT_REMOVE_TASK - result flag with the appropriate type for the
 *    remove_task controller - like function
 *  - RESULT_CHANGE_TASK_DELAY - result flag with the appropriate type for the
 *    change_task_delay controller - like function
 *
 */
enum Types_handle_events_tasks {
  RESULT_UNKNOWN =
      0, /**< undefined flag, no match with the controller function calls */
  RESULT_REGISTER_TASK = 1, /**< result flag with the appropriate type for the
                               register_task controller - like function */
  RESULT_GET_CALLBACK = 2,  /**< result flag with the appropriate type for the
                               get_callback  controller - like function */
  RESULT_REMOVE_TASK = 3,   /**< result flag with the appropriate type for the
                               remove_task   controller - like function */
  RESULT_CHANGE_TASK_DELAY =
      4, /**< result flag with the appropriate type for the change_task_delay
            controller - like function */
};

/**
 *  @details
 *  Union for handling results of @link{handle_events_tasks} function execution.
 *  Possible values @note only one of is possible!:
 *  - result_register_task - result for the register_task controller return
 *    value
 *  - result_get_callback - result for the get_callback controller return value
 *  - result_remove_task - result for the remove_task controller return value
 *  - result_change_task_delay - result for the change_task_delay controller
 *    return value
 *
 */
union Union_handle_events_tasks_results {
  PROMISE_TASK_ID
  result_register_task; /**< result for the register_task controller return
                           value */
  PROMISE_TASK
  result_get_callback; /**< result for the get_callback controller return value
                        */
  PROMISE_REMOVE_TASK
  result_remove_task; /**< result for the remove_task controller return value */
  PROMISE_CHANGE_TASK_DELAY
  result_change_task_delay; /**< result for the change_task_delay controller
                               return value */
};

/**
 *  @details
 *  Structure for handling results of @link{handle_events_tasks} function
 *  execution. I.e. the RESULT_* like types are suitable to controllers for
 *  further usage. (@link{handle_events_tasks} function just passes them on )
 *  - type - (RESULT_UNKNOWN | RESULT_REGISTER_TASK | RESULT_GET_CALLBACK |
 *              RESULT_REMOVE_TASK | RESULT_CHANGE_TASK_DELAY)
 *  - results - union @link{union Union_handle_events_tasks_results}, that is of
 *    complex custom defined types
 *    i.e. (result_register_task | result_get_callback | result_remove_task |
 *          result_change_task_delay)
 *
 *  @example
 *    ***use it inside the controller body logic. E.g. inner of the
 *    register_task() controller or inside while(1){} for FSM like logic***
 *    =>
 *    ***set up the flag***
 *    is_register_task = true;
 *
 *    ***update arguments***
 *    arguments_set_callback(func_to_call);
 *    arguments_set_func_arg(arg);
 *    arguments_set_delay(delay);
 *
 *    ***handle the events***
 *    return handle_events_tasks().results.result_register_task;
 *
 *    @note handle_events_tasks() for register_task() controller this case
 *    (under the hood) is resolves to
 *    => PROMISE_HANDLE_EVENTS_TASKS.results.result_register_task via set field
 *       type = RESULT_REGISTER_TASK;
 *
 *    PROMISE_TASK_ID log_id = register_task(some_callback, 400, 400);
 *    TASK_COUNTER task_id;
 *
 *    ***inside handle_events_function***
 *    ...
 *    if (is_register_task) {
 *      PROMISE_TASK_ID result = {};
 *      result =
 *          handle_register_task(arguments_get_callback(),
 *          arguments_get_func_arg(), arguments_get_delay());
 *      is_register_task = false;
 *      arguments_reset();
 *
 *      return (PROMISE_HANDLE_EVENTS_TASKS){
 *          .type = RESULT_REGISTER_TASK, .results.result_register_task =
 *          result};
 *    }
 *    ...
 *
 *    ***back to the scope of register_task controller execution***
 *    ...
 *    switch (log_id.type) {
 *    case SUCCESS:
 *      task_id = log_id.register_task_result.TASK_ID;
 *      printf("task_id: %hd\n", task_id);
 *      OUTPUT: e.g. 9 (task_id: 9)
 *      break;
 *    case ERROR_CODE:
 *      printf("ERROR_CODE: %hd\n",
 *        log_id.register_task_result.CODES_RESULT);
 *      OUTPUT: e.g. REGISTER_TASK_ARRAY_OF_TASKS_FULL
 *      or
 *      OUTPUT: e.g. REGISTER_TASK_TIMESPEC_GET_ERROR
 *      or
 *      OUTPUT: e.g. REGISTER_TASK_GET_ID_ERROR
 *      break;
 *    default:
 *      fprintf(stderr, "Error(%s() function at %d): ups... Unknown
 *        log_id.type\n", __func__, __LINE__);
 *      break;
 *    }
 *
 */
typedef struct s_Handle_events_tasks {
  enum Types_handle_events_tasks
      type; /**< RESULT_UNKNOWN | RESULT_REGISTER_TASK | RESULT_GET_CALLBACK |
               RESULT_REMOVE_TASK | RESULT_CHANGE_TASK_DELAY */
  union Union_handle_events_tasks_results
      results; /**< result_register_task | result_get_callback |
                  result_remove_task | result_change_task_delay  */
} PROMISE_HANDLE_EVENTS_TASKS;

#endif
