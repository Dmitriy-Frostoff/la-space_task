/**
 *  @note In the @file{task/config.h} at @type{enum Global_variables} set
 *  MAX_TASK_QUANTITY = 3 (to test all the cases below), otherwise one'll have
 *  got an "segmentation fault" error (because of incorrect @param{arr_size} and
 *  @param{elems_quantity_to_sort} in the
 *  @callback{sort_tasks_descending_by_delay_func} function)
 *
 *  Usage
 *  copy all the code below to the @file{task/main.c}, check that #include's are
 *  copied too
 *
 */

#include "./global_variables.h"
#include "./module_run_tasks_after_delay.h"

#include "./utils.h"
#include <unistd.h>

int main(void) {
  /** !Test data! */

  // check @callback{register_task} function

  // check expect error REGISTER_TASK_ARRAY_OF_TASKS_FULL
  //  (expected error_code 1)
  // setup test data
  TASK_COUNTER task_count_temp = task_count;
  task_count = MAX_TASK_QUANTITY;

  PROMISE_TASK_ID log_id = {};
  TASK_COUNTER task_id;

  log_id = register_task(show_task_info, 5, 400);

  switch (log_id.type) {
  case SUCCESS:
    task_id = log_id.register_task_result.TASK_ID;
    printf("register_task(): task was registered successfully\n");
    printf("ID: %hd\n", log_id.register_task_result.TASK_ID);
    printf("task_id: %hd\n", task_id);
    break;
  case ERROR_CODE:
    printf("register_task(): ERROR_CODE: %hd\n",
           log_id.register_task_result.REGISTER_TASK_CODES);
    break;
  default:
    fprintf(stderr, "Error(%s() function at %d): ups...\n", __func__, __LINE__);
    break;
  }

  // teardown => restore task_count value
  task_count = task_count_temp;

  // check happy path => tasks registered correctly (@type{unsigned short}
  // TASK_ID as the result)
  log_id = register_task(show_task_info, 5, 400);

  switch (log_id.type) {
  case SUCCESS:
    task_id = log_id.register_task_result.TASK_ID;
    printf("register_task(): task was registered successfully\n");
    printf("ID: %hd\n", log_id.register_task_result.TASK_ID);
    printf("task_id: %hd\n", task_id);
    break;
  case ERROR_CODE:
    printf("register_task(): ERROR_CODE: %hd\n",
           log_id.register_task_result.REGISTER_TASK_CODES);
    break;
  default:
    fprintf(stderr, "Error(%s() function at %d): ups...\n", __func__, __LINE__);
    break;
  }

  log_id = register_task(show_task_info, 15, 1400);

  switch (log_id.type) {
  case SUCCESS:
    task_id = log_id.register_task_result.TASK_ID;
    printf("register_task(): task was registered successfully\n");
    printf("ID: %hd\n", log_id.register_task_result.TASK_ID);
    printf("task_id: %hd\n", task_id);
    break;
  case ERROR_CODE:
    printf("register_task(): ERROR_CODE: %hd\n",
           log_id.register_task_result.REGISTER_TASK_CODES);
    break;
  default:
    fprintf(stderr, "Error(%s() function at %d): ups...\n", __func__, __LINE__);
    break;
  }

  log_id = register_task(show_task_info, 9, 4200);

  switch (log_id.type) {
  case SUCCESS:
    task_id = log_id.register_task_result.TASK_ID;
    printf("register_task(): task was registered successfully\n");
    printf("ID: %hd\n", log_id.register_task_result.TASK_ID);
    printf("task_id: %hd\n", task_id);
    break;
  case ERROR_CODE:
    printf("register_task(): ERROR_CODE: %hd\n",
           log_id.register_task_result.REGISTER_TASK_CODES);
    break;
  default:
    fprintf(stderr, "Error(%s() function at %d): ups...\n", __func__, __LINE__);
    break;
  }

  // case: tasks_array is full. Try to add extra task =>
  // REGISTER_TASK_ARRAY_OF_TASKS_FULL
  //  (expected error_code 1)
  log_id = register_task(show_task_info, 42, 6400);

  switch (log_id.type) {
  case SUCCESS:
    task_id = log_id.register_task_result.TASK_ID;
    printf("register_task(): task was registered successfully\n");
    printf("ID: %hd\n", log_id.register_task_result.TASK_ID);
    printf("task_id: %hd\n", task_id);
    break;
  case ERROR_CODE:
    printf("register_task(): ERROR_CODE: %hd\n",
           log_id.register_task_result.REGISTER_TASK_CODES);
    break;
  default:
    fprintf(stderr, "Error(%s() function at %d): ups...\n", __func__, __LINE__);
    break;
  }

  // manual zero the Task (do not do that anymore! use proper methods instead!)
  tasks_array[0] = (Task){0};
  task_count -= 1;
  PROMISE_ID_VALUE log_id_value = free_id(task_id);

  switch (log_id_value.type) {
  case SUCCESS:
    task_id -= 1;
    printf("free_id(): id value was freed successfully\n");
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_id_value.type\n",
            __func__, __LINE__);
    break;
  }

  // @note ! Can cause "segmentation fault" error! Check
  // @link{MAX_TASK_QUANTITY} and @param{elems_quantity_to_sort} (currently = 3)
  sort_tasks_descending_by_delay(tasks_array, MAX_TASK_QUANTITY, 3);

  log_id = register_task(show_task_info, 96, 400);

  switch (log_id.type) {
  case SUCCESS:
    task_id = log_id.register_task_result.TASK_ID;
    printf("register_task(): task was registered successfully\n");
    printf("ID: %hd\n", log_id.register_task_result.TASK_ID);
    printf("task_id: %hd\n", task_id);
    break;
  case ERROR_CODE:
    printf("register_task(): ERROR_CODE: %hd\n",
           log_id.register_task_result.REGISTER_TASK_CODES);
    break;
  default:
    fprintf(stderr, "Error(%s() function at %d): ups...\n", __func__, __LINE__);
    break;
  }

  // check @callback{get_callback} function

  // check expect error "GET_CALLBACK_ARRAY_OF_TASKS_EMPTY"
  //  (expected error_code 1)
  task_count_temp = task_count;
  task_count = 0;

  PROMISE_TASK log_task = get_callback();
  Task task = {};

  switch (log_task.type) {
  case SUCCESS:
    task = log_task.get_callback_result.TASK;
    printf("get_callback(): task was got successfully\n");
    break;
  case ERROR_CODE:
    printf("get_callback(): ERROR_CODE: %hd\n",
           log_task.get_callback_result.GET_CALLBACK_CODES);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_task.type\n",
            __func__, __LINE__);
    break;
  }

  // restore task_count value
  task_count = task_count_temp;

  // check expect error "GET_CALLBACK_PENDING"
  //  (expected error_code 3)
  log_task = get_callback();

  switch (log_task.type) {
  case SUCCESS:
    task = log_task.get_callback_result.TASK;
    printf("get_callback(): task was got successfully\n");
    break;
  case ERROR_CODE:
    printf("get_callback(): ERROR_CODE: %hd\n",
           log_task.get_callback_result.GET_CALLBACK_CODES);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_task.type\n",
            __func__, __LINE__);
    break;
  }

  // add sleep of the stream (@note it blocks the stream!)
  sleep(1);

  // check happy path => @type{Task} TASK{...} as the result
  log_task = get_callback();

  switch (log_task.type) {
  case SUCCESS:
    task = log_task.get_callback_result.TASK;
    printf("get_callback(): task was got successfully\n");
    break;
  case ERROR_CODE:
    printf("get_callback(): ERROR_CODE: %hd\n",
           log_task.get_callback_result.GET_CALLBACK_CODES);
    fprintf(stderr, "%s at %d\n", __func__, __LINE__);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_task.type\n",
            __func__, __LINE__);
    break;
  }

  // run the Task{...} with Task.func_arg
  task.callback(task.func_arg);

  // add new Task{...}
  log_id = register_task(show_task_info, 960, 960);

  switch (log_id.type) {
  case SUCCESS:
    task_id = log_id.register_task_result.TASK_ID;
    printf("register_task(): task was registered successfully\n");
    printf("ID: %hd\n", log_id.register_task_result.TASK_ID);
    printf("task_id: %hd\n", task_id);
    break;
  case ERROR_CODE:
    printf("register_task(): ERROR_CODE: %hd\n",
           log_id.register_task_result.REGISTER_TASK_CODES);
    break;
  default:
    fprintf(stderr, "Error(%s() function at %d): ups...\n", __func__, __LINE__);
    break;
  }

  // check @callback{change_task_delay} function

  // check expect error GET_CALLBACK_ARRAY_OF_TASKS_EMPTY
  //  (expected error_code 1)
  task_count_temp = task_count;
  task_count = 0;

  PROMISE_CHANGE_TASK_DELAY log_change_task_delay = change_task_delay(0, 1600);

  switch (log_change_task_delay.type) {
  case SUCCESS:
    printf("log_change_task_delay(): CHANGE_TASK_DELAY_DONE_SUCCESSFULLY\n");
    break;
  case ERROR_CODE:
    printf("log_change_task_delay(): ERROR_CODE: %hd\n",
           log_change_task_delay.CODES_RESULT);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown "
            "log_change_task_delay.type\n",
            __func__, __LINE__);
    break;
  }

  // restore task_count value
  task_count = task_count_temp;

  // check expect error CHANGE_TASK_DELAY_TASK_ID_IS_NOT_DETERMINED
  //  (expected error_code 2)

  log_change_task_delay = change_task_delay(96, 1600);

  switch (log_change_task_delay.type) {
  case SUCCESS:
    printf("log_change_task_delay(): CHANGE_TASK_DELAY_DONE_SUCCESSFULLY\n");
    break;
  case ERROR_CODE:
    printf("log_change_task_delay(): ERROR_CODE: %hd\n",
           log_change_task_delay.CODES_RESULT);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown "
            "log_change_task_delay.type\n",
            __func__, __LINE__);
    break;
  }

  // check happy path => CHANGE_TASK_DELAY_DONE_SUCCESSFULLY

  log_change_task_delay = change_task_delay(0, 1600);

  switch (log_change_task_delay.type) {
  case SUCCESS:
    printf("log_change_task_delay(): CHANGE_TASK_DELAY_DONE_SUCCESSFULLY\n");
    break;
  case ERROR_CODE:
    printf("log_change_task_delay(): ERROR_CODE: %hd\n",
           log_change_task_delay.CODES_RESULT);
    fprintf(stderr, "Error(%s() function at %d): ups...\n", __func__, __LINE__);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown "
            "log_change_task_delay.type\n",
            __func__, __LINE__);
    break;
  }

  // test @callback{remove_task} function

  // check expect error REMOVE_TASK_ARRAY_OF_TASKS_EMPTY
  //  (expected error_code 1)
  task_count_temp = task_count;
  task_count = 0;

  PROMISE_REMOVE_TASK log_remove_task = remove_task(0);

  switch (log_remove_task.type) {
  case SUCCESS:
    printf("log_remove_task(): REMOVE_TASK_DONE_SUCCESSFULLY\n");
    break;
  case ERROR_CODE:
    printf("log_remove_task(): ERROR_CODE: %hd\n",
           log_remove_task.CODES_RESULT);

    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_remove_task.type\n",
            __func__, __LINE__);
    break;
  }

  // restore task_count value
  task_count = task_count_temp;

  // check expect error REMOVE_TASK_TASK_ID_IS_NOT_DETERMINED
  //  (expected error_code 2)

  log_remove_task = remove_task(96);

  switch (log_remove_task.type) {
  case SUCCESS:
    printf("log_remove_task(): REMOVE_TASK_DONE_SUCCESSFULLY\n");
    break;
  case ERROR_CODE:
    printf("log_remove_task(): ERROR_CODE: %hd\n",
           log_remove_task.CODES_RESULT);

    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_remove_task.type\n",
            __func__, __LINE__);
    break;
  }

  // check happy path => REMOVE_TASK_DONE_SUCCESSFULLY
  log_remove_task = remove_task(0);

  switch (log_remove_task.type) {
  case SUCCESS:
    printf("log_remove_task(): REMOVE_TASK_DONE_SUCCESSFULLY\n");
    break;
  case ERROR_CODE:
    printf("log_remove_task(): ERROR_CODE: %hd\n",
           log_remove_task.CODES_RESULT);

    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_remove_task.type\n",
            __func__, __LINE__);
    break;
  }

  /** !Test data! */

  return 0;
}
