#ifndef UTILS_H
#define UTILS_H

#include "./config.h"
#include "./utils.h"

TASK_ID register_task(task_callback func_to_call, unsigned short arg,
                      unsigned short delay);
Task get_callback(void);
int remove_task(TASK_ID id);
int change_task_delay(TASK_ID id, unsigned short new_delay);
void show_task_info(unsigned short arg);

#endif
