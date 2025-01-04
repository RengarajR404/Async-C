#include<stdio.h>
#include<stdlib.h>
#include "async.h"

void print_message(void *arg) {
    printf("Task: %s\n", (char *)arg);
}
void print_loop(void *arg) {
  for (int i = 0; i < 100000; i++){
      printf("Printing numbers inside task %d,\n", i);
    }
  printf("\n\n\n\n\n\n\n\n\n\n\n\n");
}

int main() {
    AsyncLib *lib = async_lib_init();

    async_add_task(lib, print_message, "One-time Task", 1000, false); // Run after 1 second
    async_add_task(lib, print_message, "Recurring Task", 500, true); // Run every 0.5 seconds
    async_add_task(lib, print_loop, "", 500, true);
    async_run(lib); // Start the event loop (Press Ctrl+C to exit)

    async_lib_cleanup(lib);
    return 0;
}
