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

#include "./environment/global_variables.h"
#include "./module_run_tasks_after_delay.h"

#include "./utilities/utils.h"

int main(void) {
  TASK_COUNTER id = -1;

  PROMISE_ID_VALUE log_id_value = get_id();

  // get three (3) id's in a row
  // expected id = 0
  switch (log_id_value.type) {
  case SUCCESS:
    id = log_id_value.handle_id_result.ID_VALUE;
    printf("get_id(): id value was got successfully\n");
    printf("ID: %hd\n", log_id_value.handle_id_result.ID_VALUE);
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
  default:
    break;
  }

  log_id_value = get_id();
  // expected id = 1
  switch (log_id_value.type) {
  case SUCCESS:
    id = log_id_value.handle_id_result.ID_VALUE;
    printf("get_id(): id value was got successfully\n");
    printf("ID: %hd\n", log_id_value.handle_id_result.ID_VALUE);
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
  default:
    break;
  }

  log_id_value = get_id();
  // expected id = 2
  switch (log_id_value.type) {
  case SUCCESS:
    id = log_id_value.handle_id_result.ID_VALUE;
    printf("get_id(): id value was got successfully\n");
    printf("ID: %hd\n", log_id_value.handle_id_result.ID_VALUE);
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
  default:
    break;
  }

  log_id_value = get_id();
  // expect error at getting 4th id (i.e. id = 3) HANDLE_ID_NO_FREE_ID
  // (error_code 1)
  switch (log_id_value.type) {
  case SUCCESS:
    id = log_id_value.handle_id_result.ID_VALUE;
    printf("get_id(): id value was got successfully\n");
    printf("ID: %hd\n", log_id_value.handle_id_result.ID_VALUE);
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
  default:
    break;
  }

  // free the id
  log_id_value = free_id(id);

  switch (log_id_value.type) {
  case SUCCESS:
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

  // reduce id (expected id = 2 => id = 1)
  id -= 1;

  log_id_value = get_id();
  // get the id, expected id = 2
  switch (log_id_value.type) {
  case SUCCESS:
    id = log_id_value.handle_id_result.ID_VALUE;
    printf("get_id(): id value was got successfully\n");
    printf("ID: %hd\n", log_id_value.handle_id_result.ID_VALUE);
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
  default:
    break;
  }

  // free the id
  log_id_value = free_id(id);

  switch (log_id_value.type) {
  case SUCCESS:
    printf("free_id(): id value was freed successfully\n");
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_id_value.type\n",
            __func__, __LINE__);
    break;
  }

  // reduce id (id = 2 => id = 1)
  id -= 1;

  // free the id
  log_id_value = free_id(id);

  switch (log_id_value.type) {
  case SUCCESS:
    printf("free_id(): id value was freed successfully\n");
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_id_value.type\n",
            __func__, __LINE__);
    break;
  }

  // reduce id (id = 1 => id = 0)
  id -= 1;

  // free the id
  log_id_value = free_id(id);

  switch (log_id_value.type) {
  case SUCCESS:
    printf("free_id(): id value was freed successfully\n");
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_id_value.type\n",
            __func__, __LINE__);
    break;
  }

  // reduce id  (id = 0 => id = -1 => 65536 - 1 = 65535)
  id -= 1;

  // free the id
  // expected error: HANDLE_ID_UNKNOWN_ID (error_code 2)
  log_id_value = free_id(id);

  switch (log_id_value.type) {
  case SUCCESS:
    printf("free_id(): id value was freed successfully\n");
    break;
  case ERROR_CODE:
    printf("ERROR_CODE: %hd\n", log_id_value.handle_id_result.CODES_RESULT);
    break;
  default:
    fprintf(stderr,
            "Error(%s() function at %d): ups... Unknown log_id_value.type\n",
            __func__, __LINE__);
    break;
  }

  return 0;
}
