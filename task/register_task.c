#include "./utils.h"

extern TASK_ID task_count;
extern Task tasks_array[MAX_TASK_QUANTITY];

TASK_ID register_task(task_callback func_to_call, unsigned short arg,
                      unsigned short delay) {
  // TODO(dmitriy-frostoff/register_task)! Create custom exit code for that case
  // !
  // prevent adding excessive task
  if (task_count >= MAX_TASK_QUANTITY) {
    return 0;
  }

  // create Task instance
  Task task = {};

  // set up current timestamp
  struct timespec ts = {};
  int written_var_count = timespec_get(&ts, TIME_UTC);

  // TODO(dmitriy-frostoff/register_task)! Create custom exit code for that case
  // !
  // ts.tv_sec and ts.tv_nsec are set ? => 1(OK) (two fileds are set, 1 is base
  // for @link{TIME_UTC})
  if (written_var_count == 0) {
    return 0;
  }

  // set up the @link{task.created_timespec}
  task.created_timespec = ts;

  // set up the @link{callback}
  task.callback = func_to_call;

  // set up the @link{task.func_arg}
  task.func_arg = arg;

  // set up the @link{task.delay}
  task.delay = delay;

  // set up the @link{task.id}
  task.id = task_count;

  // nest the task instance to the @kink{tasks_array}
  tasks_array[task_count] = task;

  // update @link{task_count} counter
  task_count += 1;

  // sort tasks in the @link{tasks_array} descending (over the @link{Task.delay}
  // field value) i.e. the least delay has greater index
  // @note if @link{tasks_array} contains at least two tasks and the added
  // task's delay is greater than min delay for sort
  if (task_count > 1 && task.delay > MIN_DELAY_FOR_SORT) {
    qsort(tasks_array, task_count + 1, sizeof(Task), qsort_compare_func);
  }

  return task_count;
}
