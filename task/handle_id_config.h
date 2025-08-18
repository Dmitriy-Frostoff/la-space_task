#ifndef HANDLE_ID_H
#define HANDLE_ID_H

#include "./config.h"

/**
 *  @details
 *  - HANDLE_ID_DONE_SUCCESSFULLY - no errors, done successfully
 *  - HANDLE_ID_NO_FREE_ID - no free id is avaliable
 *  - HANDLE_ID_UNKNOWN_ID - the id is not defined
 *
 */
enum Handle_id_errors_codes {
  HANDLE_ID_DONE_SUCCESSFULLY = 0, /**< no errors, done successfully */
  HANDLE_ID_NO_FREE_ID = 1,        /**< no free id is avaliable */
  HANDLE_ID_UNKNOWN_ID = 2,        /**< the id is not defined */
};

/**
 *  @details
 *  Union for handling results of @link{get_id} or @link{free_id} functions
 *  execution. Possible values
 *  @note only one of is possible!:
 *  - ID_VALUE - free ID number
 *  - CODES_RESULT - Error codes at the process of id handling
 *
 */
union Union_id_value {
  unsigned short ID_VALUE; /**< free ID number */
  enum Handle_id_errors_codes
      CODES_RESULT; /**< Error codes at the process of id handling */
};

/**
 *  @details
 *  Structure for handling results of @link{get_id} or @link{free_id}
 *  function execution.
 *  - type - (SUCCESS | ERROR_CODE)
 *  - handle_id_result - union @link{union Union_id_value}, that is
 *    @type{unsigned short} for ID_VALUE (SUCCESS, everything is OK)
 *    ( @note CODES_RESULT with HANDLE_ID_DONE_SUCCESSFULLY is only for
 *    SUCCESS for unification with other PROMISE_* like structures)
 *    or
 *    one of error codes for ERROR_CODE
 *    i.e. (HANDLE_ID_NO_FREE_ID |
 *    HANDLE_ID_UNKNOWN_ID)
 *
 *  @example
 *    *** Predefined context ***
 *    static ID_LIST_ELEM id_storage_array[3] = {0};
 *    ID_LIST_ELEM *ptr_head_elem = NULL;
 *    TASK_COUNTER id;
 *    *** Usage ***
 *    PROMISE_ID_VALUE log_id_value = get_id();
 *
 *    switch (log_id_value.type) {
 *    case SUCCESS:
 *      id = log_id_value.handle_id_result.ID_VALUE;
 *      printf("get_id(): id value was got successfully\n");
 *      printf("ID: %hd\n", log_id_value.handle_id_result.ID_VALUE);
 *      break;
 *      ***
 *      id = 0
 *      *ptr_head_elem {
 *        id = 0
 *        is_free = false
 *        next = address of the next free id node (i.e. &id_storage_array[1])
 *      }
 *    case ERROR_CODE:
 *      printf("ERROR_CODE: %hd\n",
 *        log_id_value.handle_id_result.CODES_RESULT);
 *      break;
 *      OUTPUT: e.g. HANDLE_ID_NO_FREE_ID
 *    default:
 *      fprintf(stderr, "Error(%s() function at %d): ups... Unknown
 *        log_id_value.type\n", __func__, __LINE__);
 *      break;
 *    }
 *
 *    PROMISE_ID_VALUE log_id_value = free_id(TASK_COUNTER id);
 *
 *    switch (log_id_value.type) {
 *    case SUCCESS:
 *      printf("free_id(): id value was freed successfully\n");
 *      break;
 *    case ERROR_CODE:
 *      printf("ERROR_CODE: %hd\n",
 *        log_id_value.handle_id_result.CODES_RESULT);
 *      break;
 *      OUTPUT: e.g. HANDLE_ID_UNKNOWN_ID
 *    default:
 *      fprintf(stderr, "Error(%s() function at %d): ups... Unknown
 *        log_id_value.type\n", __func__, __LINE__);
 *      break;
 *    }
 *
 */
typedef struct s_Handle_id_result {
  PROMISE_TYPE type;                     /**< SUCCESS | ERROR_CODE */
  union Union_id_value handle_id_result; /**< ID_VALUE | CODES_RESULT */
} PROMISE_ID_VALUE;

/**
 *  @details
 *  Structure to implement singly Pointer-Based linked list on array (LIFO).
 *  - TASK_COUNTER id - id value of the current node
 *  - bool is_free - boolean flag to prevent multiple call for freeing id
 *  - struct s_Linked_list_id_item *next - pointer to the next node of the
 *    Linked List
 *
 */
typedef struct s_Linked_list_id_item {
  TASK_COUNTER id; /**< id value of the current node */
  bool is_free;    /**< boolean flag to prevent multiple call for freeing id */
  struct s_Linked_list_id_item *next; /**< pointer to the next node */
} ID_LIST_ELEM;

PROMISE_ID_VALUE get_id(void);
PROMISE_ID_VALUE free_id(TASK_COUNTER id);

#endif
