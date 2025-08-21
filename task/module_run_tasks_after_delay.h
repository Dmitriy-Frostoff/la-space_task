#ifndef MODULE_RUN_TASKS_AFTER_DELAY_H
#define MODULE_RUN_TASKS_AFTER_DELAY_H

#include "./change_task_delay_config.h"
#include "./config.h"
#include "./get_callback_config.h"
#include "./handle_events_tasks_config.h"
#include "./register_task_config.h"
#include "./remove_task_config.h"

PROMISE_HANDLE_EVENTS_TASKS handle_events_tasks(void);
PROMISE_TASK_ID register_task(task_callback func_to_call, unsigned short arg,
                              unsigned short delay);
PROMISE_TASK get_callback(void);
PROMISE_REMOVE_TASK remove_task(TASK_COUNTER id);
PROMISE_CHANGE_TASK_DELAY change_task_delay(TASK_COUNTER id,
                                            unsigned short new_delay);
void show_task_info(unsigned short arg);

#endif
