#ifndef UTILS_H
#define UTILS_H

#include "./config.h"

TASK_ID register_task(task_callback, unsigned short arg, unsigned short delay);
Task get_callback(void);
int remove_task(unsigned short id);
int change_task_delay(unsigned short id, unsigned short new_delay);
void show_task_info(unsigned short arg);

#endif
