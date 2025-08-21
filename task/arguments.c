#include "./arguments_config.h"

// boolean flags for the tasks events methods

bool is_register_task =
    false; /**< boolean flag for register_task controller handling */
bool is_get_callback =
    false; /**< boolean flag for get_callback controller handling */
bool is_remove_task =
    false; /**< boolean flag for remove_task controller handling */
bool is_change_task_delay =
    false; /**< boolean flag for change_task_delay controller handling */

// private variables

static Arguments arguments = {0};

// declare @link{arguments} getters and setters

/**
 *  @brief getter for the callback field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @param {void} - no param expected
 *
 *  @return {task_callback} - arguments.callback pointer
 *
 *  @example
 *    arguments_get_callback() => address of the callback to call (e.g.
 *    @see{show_task_info} )
 *    arguments{
 *      callback = 0x7ffe5367e064,
 *      func_arg = 0,
 *      delay = 0,
 *      patch_delay = 0,
 *      id = 0,
 *      id_remove = 0,
 *    };
 *
 */
task_callback arguments_get_callback(void) {
  return arguments.callback;
}

/**
 *  @brief getter for the func_arg field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @param {void} - no param expected
 *
 *  @return {unsigned short} - arguments.func_arg value (argument for the
 *  arguments.callback further call)
 *
 *  @example
 *    arguments{
 *      callback = 0x0,
 *      func_arg = 5,
 *      delay = 0,
 *      patch_delay = 0,
 *      id = 0,
 *      id_remove = 0,
 *    };
 *
 */
unsigned short arguments_get_func_arg(void) {
  return arguments.func_arg;
}

/**
 *  @brief getter for the delay field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @param {void} - no param expected
 *
 *  @return {unsigned short} - arguments.delay value (ms)
 *
 *  @example
 *    arguments_get_delay() => 400 (400ms)
 *    =>
 *    arguments{
 *      callback = 0x0,
 *      func_arg = 0,
 *      delay = 400,
 *      patch_delay = 0,
 *      id = 0,
 *      id_remove = 0,
 *    };
 *
 */
unsigned short arguments_get_delay(void) {
  return arguments.delay;
}

/**
 *  @brief getter for the patch_delay field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @note patch_delay is for updating the task's current delay (replacing)
 *
 *  @param {void} - no param expected
 *
 *  @return {unsigned short} - arguments.patch_delay value (ms)
 *
 *  @example
 *    arguments_get_delay() => 800 (800ms)
 *    =>
 *    arguments{
 *      callback = 0x0,
 *      func_arg = 0,
 *      delay = 0,
 *      patch_delay = 800,
 *      id = 0,
 *      id_remove = 0,
 *    };
 *
 */
unsigned short arguments_get_patch_delay(void) {
  return arguments.patch_delay;
}

/**
 *  @brief getter for the id field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @param {void} - no param expected
 *
 *  @return {unsigned short} - arguments.id value
 *
 *  @example
 *    arguments_get_id() => 9 (id = 9, but it's a 10th task)
 *    =>
 *    arguments{
 *      callback = 0x0,
 *      func_arg = 0,
 *      delay = 0,
 *      patch_delay = 0,
 *      id = 9,
 *      id_remove = 0,
 *    };
 *
 */
unsigned short arguments_get_id(void) {
  return arguments.id;
}

/**
 *  @brief getter for the id_remove field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @note id_remove i.e. id of the task for further removing and freeing the id
 *  (id_remove)
 *
 *  @param {void} - no param expected
 *
 *  @return {unsigned short} - arguments.id_remove value
 *
 *  @example
 *    arguments_get_id() => 0 (id = 0, but it's a 1st task)
 *    =>
 *    arguments{
 *      callback = 0x0,
 *      func_arg = 0,
 *      delay = 0,
 *      patch_delay = 0,
 *      id = 0,
 *      id_remove = 0,
 *    };
 *
 */
unsigned short arguments_get_id_remove(void) {
  return arguments.id_remove;
}

/**
 *  @brief setter for the callback field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @note ! Impure function !
 *  - depends on custom defined @type{task_callback}
 *
 *  @param {task_callback} callback - callback for the task structure to
 *  call after delay time gone
 *
 *  @example
 *    arguments_set_callback(show_task_info) => void
 *    =>
 *    arguments{
 *      callback = 0x7ffe5367e064, // address of the show_task_info function
 *      func_arg = 0,
 *      delay = 0,
 *      patch_delay = 0,
 *      id = 0,
 *      id_remove = 0,
 *    };
 *
 */
void arguments_set_callback(task_callback callback) {
  arguments.callback = callback;
}

/**
 *  @brief setter for the func_arg field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @param {unsigned short} func_arg - argument for the callback of the task
 *  structure to be called with
 *
 *  @example
 *    arguments_set_func_arg(5) => void
 *    =>
 *    arguments{
 *      callback = 0x0
 *      func_arg = 5,
 *      delay = 0,
 *      patch_delay = 0,
 *      id = 0,
 *      id_remove = 0,
 *    };
 *
 */
void arguments_set_func_arg(unsigned short func_arg) {
  arguments.func_arg = func_arg;
}

/**
 *  @brief setter for the delay field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @param {unsigned short} delay - delay value(ms) for freezing the task
 *  callback with func_arg calling
 *
 *  @example
 *    arguments_set_delay(400) => void
 *    =>
 *    arguments{
 *      callback = 0x0
 *      func_arg = 0,
 *      delay = 400,
 *      patch_delay = 0,
 *      id = 0,
 *      id_remove = 0,
 *    };
 *
 */
void arguments_set_delay(unsigned short delay) {
  arguments.delay = delay;
}

/**
 *  @brief setter for the patch_delay field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @param {unsigned short} patch_delay - updated delay value(ms) for freezing
 *  the task callback with func_arg calling
 *  @note updated patch_delay value recreates the task timestamp and delay
 *  starts from the beginning
 *
 *  @example
 *    arguments_set_patch_delay(800) => void
 *    =>
 *    arguments{
 *      callback = 0x0
 *      func_arg = 0,
 *      delay = 0,
 *      patch_delay = 800,
 *      id = 0,
 *      id_remove = 0,
 *    };
 *
 */
void arguments_set_patch_delay(unsigned short patch_delay) {
  arguments.patch_delay = patch_delay;
}

/**
 *  @brief setter for the id field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @param {unsigned short} id - the task id for further handling
 *
 *  @example
 *    arguments_set_id(9) => void
 *    =>
 *    arguments{
 *      callback = 0x0
 *      func_arg = 0,
 *      delay = 0,
 *      patch_delay = 0,
 *      id = 9,
 *      id_remove = 0,
 *    };
 *
 */
void arguments_set_id(unsigned short id) {
  arguments.id = id;
}

/**
 *  @brief setter for the id field of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *  @note id_remove i.e. id of the task for further removing and freeing the id
 *  (id_remove)
 *
 *  @param {unsigned short} id_remove - arguments.id_remove value
 *
 *  @example
 *    arguments_set_id_remove(0) => void
 *    =>
 *    arguments.id_remove = 0
 *    arguments{
 *      callback = 0x0
 *      func_arg = 0,
 *      delay = 0,
 *      patch_delay = 0,
 *      id = 0,
 *      id_remove = 0, // the task with id 0 will be removed and id 0 will
 *                        be freed
 *    };
 *
 */
void arguments_set_id_remove(unsigned short id_remove) {
  arguments.id_remove = id_remove;
}

/**
 *  @brief Reset the fields of the encapsulated @type{Arguments}
 *  @link{arguments} structure
 *
 *   @note -1 => 65536 - 1 => 65535
 *   because they're of type unsigned short ( @see{Arguments} type)
 *
 *  @param {void} - no params expected
 *
 *  @example
 *    static Arguments arguments = {
 *      .callback = show_task_info,
 *      .func_arg = 5,
 *      .delay = 400,
 *      .patch_delay = 800,
 *      .id = 9,
 *      .id_remove = 0,
 *    };
 *
 *    arguments_reset() => void
 *    =>
 *    arguments{
 *      callback = 0x0,
 *      func_arg = 65535,
 *      delay = 65535,
 *      patch_delay = 65535,
 *      id = 65535,
 *      id_remove = 65535,
 *    };
 *
 */
void arguments_reset(void) {
  arguments.callback = NULL;
  arguments.func_arg = -1;
  arguments.delay = -1;
  arguments.patch_delay = -1;
  arguments.id = -1;
  arguments.id_remove = -1;
}
