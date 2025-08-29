# set the 'task' folder as cwd
cd './task'

# compile '.exe' file for Windows via gcc compiler
gcc -g -I. -std=c23 \
./controllers/change_task_delay.c \
./controllers/get_callback.c \
./controllers/register_task.c \
./controllers/remove_task.c \
./environment/arguments.c \
./environment/global_variables.c \
./main.c \
./model/handle_change_task_delay.c \
./model/handle_events_tasks.c \
./model/handle_get_callback.c \
./model/handle_register_task.c \
./model/handle_remove_task.c \
./show_task_info.c \
./utilities/handle_id.c \
./utilities/sort_tasks_descending_by_delay_func.c \
-o main.exe

echo "Compilation finished with exit code $?"
