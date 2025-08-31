#include "../environment/config.h"
#include "./handle_id_config.h"

static ID_LIST_ELEM id_storage_array[MAX_TASK_QUANTITY] = {0};
static bool is_first_call = true;
ID_LIST_ELEM *ptr_free_elem = NULL;

/**
 *  @brief Utility function (encapsiulated) to initialize the Pointer-Based
 *  Linked List (array based)
 *
 *  @note ! Impure function !
 *  - mutates the outer (encapsulated in the module) @link{id_storage_array}
 *  - mutates the outer (encapsulated in the module) @link{is_first_call}
 *  - mutates the outer (encapsulated in the module) @link{ptr_free_elem}
 *
 *  @param {void} - no params expected
 *
 *  @example
 *    *** predefined ***
 *    MAX_TASK_QUANTITY = 3
 *    *** usage ***
 *    just run init_id_storage_array() => void
 *    id_storage_array[]{
 *      ID_LIST_ELEM{
 *        id = 0
 *        is_free = true
 *        next->ID_LIST_ELEM{
 *          id = 1
 *          is_free = true
 *          next->ID_LIST_ELEM{...}
 *        }
 *      },
 *      ID_LIST_ELEM{
 *        id = 1
 *        is_free = true
 *        next->ID_LIST_ELEM{
 *          id = 2
 *          is_free = true
 *          next->ID_LIST_ELEM{...}
 *        }
 *      },
 *      ID_LIST_ELEM{
 *        id = 2
 *        is_free = true
 *        next->NULL
 *      },
 *    }
 *    is_first_call = false
 *    ptr_free_elem = &id_storage_array[0]
 *
 */
static void init_id_storage_array(void) {
  // prevent multiple initializing
  // not first call ? => return
  if (!is_first_call) {
    return;
  }

  // handle from [0; MAX_TASK_QUANTITY - 1) =>
  // i.e till the penaltimate one (@note will have handle last elem after this)
  for (int i = 0; i < MAX_TASK_QUANTITY - 1; i += 1) {
    id_storage_array[i].id = i;
    id_storage_array[i].is_free = true;
    id_storage_array[i].next = &id_storage_array[i + 1];
  }

  // handle last node personally
  // just to not reassign last elem.next value
  id_storage_array[MAX_TASK_QUANTITY - 1].id = MAX_TASK_QUANTITY - 1;
  id_storage_array[MAX_TASK_QUANTITY - 1].is_free = true;
  // no next node after that
  id_storage_array[MAX_TASK_QUANTITY - 1].next = NULL;

  // set up @link{ptr_free_elem}
  ptr_free_elem = &id_storage_array[0];

  // set up calling flag
  is_first_call = false;
}

/**
 *  @brief Get the free id from the @link{id_storage_array}
 *
 *  @note ! Impure function !
 *  - mutates the outer (encapsulated in the module) @link{id_storage_array}
 *  - mutates the outer (encapsulated in the module) @link{is_first_call}
 *  - mutates the outer (encapsulated in the module) @link{ptr_free_elem}
 *  - mutates the outer (encapsulated in the module) @type{PROMISE_ID_VALUE}
 *
 *  @note Returns promise like structure @link{PROMISE_ID_VALUE}! Examine the
 *  example below how to handle it properly!
 *
 *  @param {void} - no params expected
 *
 *  @return {PROMISE_ID_VALUE} - structure of complex type
 *    @see{PROMISE_ID_VALUE} for details and examples below for clarification
 *    how to handle it
 *  @throw PROMISE_ID_VALUE.type = ERROR_CODE
 *    - PROMISE_ID_VALUE.handle_id_result.CODES_RESULT =>
 *      - HANDLE_ID_NO_FREE_ID - no free id is avaliable
 *
 *  @example
 *    ** Predefined context ***
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
 */
PROMISE_ID_VALUE get_id(void) {
  // init @link{id_storage_array} if it wasn't yet
  init_id_storage_array();

  // check the free node of @link{id_storage_array} with id exist
  if (ptr_free_elem == NULL) {
    return (PROMISE_ID_VALUE){.type = ERROR_CODE,
                              .handle_id_result.CODES_RESULT =
                                  HANDLE_ID_NO_FREE_ID};
  }

  ID_LIST_ELEM *current_node = ptr_free_elem;
  ptr_free_elem = ptr_free_elem->next;
  current_node->is_free = false;

  return (PROMISE_ID_VALUE){.type = SUCCESS,
                            .handle_id_result.ID_VALUE = current_node->id};
}

/**
 *  @brief Free the given @link{id} for further usage from the
 *  @link{id_storage_array}
 *
 *  @note ! Impure function !
 *  - mutates the outer (encapsulated in the module) @link{id_storage_array}
 *  - mutates the outer (encapsulated in the module) @link{is_first_call}
 *  - mutates the outer (encapsulated in the module) @link{ptr_free_elem}
 *  - mutates the outer (encapsulated in the module) @type{PROMISE_ID_VALUE}
 *  - mutates the outer (encapsulated in the module) @type{TASK_COUNTER}
 *
 *  @note Returns promise like structure @link{PROMISE_ID_VALUE}! Examine the
 *  example below how to handle it properly!
 *
 *  @param {TASK_COUNTER} id - id (number) to free
 *
 *  @return {PROMISE_ID_VALUE} - structure of complex type
 *    @see{PROMISE_ID_VALUE} for details and examples below for clarification
 *    how to handle it
 *    @note This's only for unification! PROMISE_ID_VALUE.type = SUCCESS
 *    - PROMISE_ID_VALUE.handle_id_result.CODES_RESULT =>
 *      HANDLE_ID_DONE_SUCCESSFULLY - no errors, done successfully
 *
 *  @throw PROMISE_ID_VALUE.type = ERROR_CODE
 *    - PROMISE_ID_VALUE.handle_id_result.CODES_RESULT =>
 *      - HANDLE_ID_UNKNOWN_ID - no free id is avaliable
 *
 *  @example
 *    *** Predefined context ***
 *    static ID_LIST_ELEM id_storage_array[3] = {0};
 *    ID_LIST_ELEM *ptr_head_elem = NULL;
 *    TASK_COUNTER id;
 *    *** Usage ***
 *    PROMISE_ID_VALUE log_id_value = get_id();
 *    ***
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
PROMISE_ID_VALUE free_id(TASK_COUNTER id) {
  // init @link{id_storage_array} if it wasn't yet
  init_id_storage_array();

  // check that @link{id} in range
  if (id < 0 || id >= MAX_TASK_QUANTITY) {
    return (PROMISE_ID_VALUE){.type = ERROR_CODE,
                              .handle_id_result.CODES_RESULT =
                                  HANDLE_ID_UNKNOWN_ID};
  }

  // get current node via given @link{id}
  ID_LIST_ELEM *current_node = &id_storage_array[id];

  // prevent unnecessary multiple freeing
  if (current_node->is_free) {
    return (PROMISE_ID_VALUE){.type = SUCCESS,
                              .handle_id_result.CODES_RESULT =
                                  HANDLE_ID_DONE_SUCCESSFULLY};
  }

  // free the id and update @link{ptr_free_elem}
  current_node->next = ptr_free_elem;
  ptr_free_elem = current_node;
  current_node->is_free = true;

  // return happy path data
  return (PROMISE_ID_VALUE){.type = SUCCESS,
                            .handle_id_result.CODES_RESULT =
                                HANDLE_ID_DONE_SUCCESSFULLY};
}
