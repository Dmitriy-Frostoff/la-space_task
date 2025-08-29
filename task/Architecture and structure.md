### Structure

./task
├── Architecture and structure.md
├── controllers
│ ├── change_task_delay.c
│ ├── get_callback.c
│ ├── register_task.c
│ └── remove_task.c
├── environment
│ ├── arguments.c
│ ├── arguments.h
│ ├── arguments_config.h
│ ├── config.h
│ ├── global_variables.c
│ └── global_variables.h
├── main.c
├── model
│ ├── change_task_delay_config.h
│ ├── get_callback_config.h
│ ├── handle_change_task_delay.c
│ ├── handle_events_tasks.c
│ ├── handle_events_tasks.h
│ ├── handle_events_tasks_config.h
│ ├── handle_get_callback.c
│ ├── handle_register_task.c
│ ├── handle_remove_task.c
│ ├── register_task_config.h
│ └── remove_task_config.h
├── module_run_tasks_after_delay.h
├── show_task_info.c
├── technical specification.md
├── tests
│ ├── handle_id.test.c
│ └── main.tests.c
└── utilities
├── handle_id.c
├── handle_id_config.h
├── sort_tasks_descending_by_delay_func.c
└── utils.h

---

#### Environment

config.h

global_variables.h  
global_variables.c

arguments.h
arguments_config.h
arguments.c

#### Model layer

handle_events_tasks.h  
handle_events_tasks_config.h  
handle_events_tasks.c

register_task_config.h  
handle_register_task.c

get_callback_config.h  
handle_get_callback.c

change_task_delay_config.h  
handle_change_task_delay.c

remove_task_config.h  
handle_remove_task.c

#### Utilities

utils.h  
sort_tasks_descending_by_delay_func.c  
handle_id_config.h  
handle_id.c

#### Methods to use as module one (i.e. like a lib)

module_run_tasks_after_delay.h

---

#### Controllers

register_task.c  
get_callback.c  
change_task_delay.c  
remove_task.c

---

> [!NOTE] example callback to use, cwd

show_task_info.c

---

### Tests

> [!NOTE] partially manual tests scenarios

handle_id.test.c
main.tests.c

---

### Usage

Include `module_run_tasks_after_delay.h`,
than nest to the top of while(1) (above the `usleep(micros_you_wish)` ) `handle_events_tasks()`;
Call one of the `contoller layer` functions and check the results (see examples in the functions).

Call stack for the `contoller layer` functions under the hood is based on MVC model, so after one of the `contoller layer` functions calling, the execution steps into the `handle_events_tasks` function (it's a controllers heart) to handle arguments and skip them further and then to call the correspondent handle function with that `arguments` from the `model` to get the result and return it back to the callee controller.

**TODO!**  
Try to recreate logic of the `while(1)` + `handle_events_tasks()` + `usleep(micros)` in a external thread.

**Desired logic**: the main thread is not blocked, user can create any logic inside `main()` with functions from the `module_run_tasks_after_delay.h` and manually check the ready one to call tasks (structure with functions and with their arguments) that act particularly like `setTimeout` from `JavaScript` / `TypeScript`.
