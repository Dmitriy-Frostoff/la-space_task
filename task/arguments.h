#ifndef ARGUMENTS__H
#define ARGUMENTS__H

#include "./config.h"
#include "./handle_events_tasks.h"

task_callback arguments_get_callback(void);
unsigned short arguments_get_func_arg(void);
unsigned short arguments_get_delay(void);
unsigned short arguments_get_patch_delay(void);
unsigned short arguments_get_id(void);
unsigned short arguments_get_id_remove(void);

void arguments_set_callback(task_callback callback);
void arguments_set_func_arg(unsigned short func_arg);
void arguments_set_delay(unsigned short delay);
void arguments_set_patch_delay(unsigned short patch_delay);
void arguments_set_id(unsigned short id);
void arguments_set_id_remove(unsigned short id_remove);

void arguments_reset(void);

#endif
