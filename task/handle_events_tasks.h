#ifndef HANDLE_EVENTS_TASKS_H
#define HANDLE_EVENTS_TASKS_H

#include "./change_task_delay_config.h"
#include "./config.h"
#include "./get_callback_config.h"
#include "./handle_events_tasks_config.h"
#include "./register_task_config.h"
#include "./remove_task_config.h"

PROMISE_TASK_ID handle_register_task(task_callback func_to_call,
                                     unsigned short arg, unsigned short delay);
PROMISE_TASK handle_get_callback(void);
PROMISE_REMOVE_TASK handle_remove_task(TASK_COUNTER id);
PROMISE_CHANGE_TASK_DELAY handle_change_task_delay(TASK_COUNTER id,
                                                   unsigned short new_delay);

#endif
