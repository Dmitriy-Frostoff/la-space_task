#include "./handle_events_tasks.h"
#include "../environment/arguments.h"
#include "./handle_events_tasks_config.h"

extern bool
    is_register_task; /**< boolean flag for register_task controller handling */
extern bool
    is_get_callback; /**< boolean flag for get_callback controller handling */
extern bool
    is_remove_task; /**< boolean flag for remove_task controller handling */
extern bool is_change_task_delay; /**< boolean flag for change_task_delay
                                     controller handling */

/**
 *  @brief Handler function to process the logic of incoming controllers calls.
 *
 *  @note ! Impure function !
 *  - mutates the global vraible @link{is_register_task}
 *  - mutates the global vraible @link{is_get_callback}
 *  - mutates the global vraible @link{is_remove_task}
 *  - mutates the global vraible @link{is_change_task_delay}
 *
 *  - implicit dependency on @type{PROMISE_TASK_ID}
 *  - implicit dependency on @type{PROMISE_TASK}
 *  - implicit dependency on @type{PROMISE_REMOVE_TASK}
 *  - implicit dependency on @type{PROMISE_CHANGE_TASK_DELAY}
 *
 *  - implicit dependency on @callback{handle_register_task}
 *  - implicit dependency on @callback{handle_get_callback}
 *  - implicit dependency on @callback{handle_remove_task}
 *  - implicit dependency on @callback{handle_change_task_delay}
 *
 *  - implicit dependency on @callback{arguments_get_callback}
 *  - implicit dependency on @callback{arguments_get_func_arg}
 *  - implicit dependency on @callback{arguments_get_delay}
 *  - implicit dependency on @callback{arguments_get_id_remove}
 *  - implicit dependency on @callback{arguments_get_id}
 *  - implicit dependency on @callback{arguments_get_patch_delay}
 *  - implicit dependency on @callback{arguments_reset}
 *
 *  @note Returns promise like structure @link{PROMISE_HANDLE_EVENTS_TASKS}!
 *  Examine the example below how to handle it properly!
 *
 *  @return {PROMISE_HANDLE_EVENTS_TASKS} -  structure of a complex type
 *    @see{PROMISE_HANDLE_EVENTS_TASKS} for details and examples below for
 *    clarification how to handle it
 *  @throw PROMISE_HANDLE_EVENTS_TASKS.type = RESULT_UNKNOWN - if no controller
 *    with it's handler and appropriate boolean flag specified
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
PROMISE_HANDLE_EVENTS_TASKS handle_events_tasks(void) {
  // handle the controllers
  if (is_register_task) {
    PROMISE_TASK_ID result = {};
    result =
        handle_register_task(arguments_get_callback(), arguments_get_func_arg(),
                             arguments_get_delay());
    is_register_task = false;
    arguments_reset();

    return (PROMISE_HANDLE_EVENTS_TASKS){
        .type = RESULT_REGISTER_TASK, .results.result_register_task = result};
  }

  if (is_get_callback) {
    PROMISE_TASK result = {};
    result = handle_get_callback();
    is_get_callback = false;
    arguments_reset();

    return (PROMISE_HANDLE_EVENTS_TASKS){.type = RESULT_GET_CALLBACK,
                                         .results.result_get_callback = result};
  }

  if (is_remove_task) {
    PROMISE_REMOVE_TASK result = {};
    result = handle_remove_task(arguments_get_id_remove());
    is_remove_task = false;
    arguments_reset();

    return (PROMISE_HANDLE_EVENTS_TASKS){.type = RESULT_REMOVE_TASK,
                                         .results.result_remove_task = result};
  }

  if (is_change_task_delay) {
    PROMISE_CHANGE_TASK_DELAY result = {};
    result = handle_change_task_delay(arguments_get_id(),
                                      arguments_get_patch_delay());
    is_change_task_delay = false;
    arguments_reset();

    return (PROMISE_HANDLE_EVENTS_TASKS){.type = RESULT_CHANGE_TASK_DELAY,
                                         .results.result_change_task_delay =
                                             result};
  }

  // handle the unspecified controller call
  return (PROMISE_HANDLE_EVENTS_TASKS){.type = RESULT_UNKNOWN};
}
