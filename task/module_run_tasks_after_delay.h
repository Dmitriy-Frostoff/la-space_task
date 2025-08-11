#ifndef MODULE_RUN_TASKS_AFTER_DELAY_H
#define MODULE_RUN_TASKS_AFTER_DELAY_H

#include "./config.h"

PROMISE_TASK_ID register_task(task_callback func_to_call, unsigned short arg,
                              unsigned short delay);
Task get_callback(void);
int remove_task(TASK_COUNTER id);
int change_task_delay(TASK_COUNTER id, unsigned short new_delay);
void show_task_info(unsigned short arg);

#endif
