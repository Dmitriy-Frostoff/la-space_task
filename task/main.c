#include "./environment/global_variables.h"
#include "./module_run_tasks_after_delay.h"

int main(void) {
  while (true) {
    // !caution improper FSM logic implementation!
    // TODO! Fix this to desired logic from the ./Architecture and structure.md
    // !
    handle_events_tasks();
    usleep(100'000);
  }
}
