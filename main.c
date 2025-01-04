#include<stdio.h>
#include<stdlib.h>
#include "async.h"

void print_message(void *arg) {
    printf("Task: %s\n", (char *)arg);
}

int main() {
    AsyncLib *lib = async_lib_init();

    async_add_task(lib, print_message, "One-time Task", 1000, true); // Run after 1 second
    async_add_task(lib, print_message, "Recurring Task", 500, true); // Run every 0.5 seconds

    async_run(lib); // Start the event loop (Press Ctrl+C to exit)

    async_lib_cleanup(lib);
    return 0;
}
