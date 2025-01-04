#ifndef CUSTOM_ASYNC_H
#define CUSTOM_ASYNC_H

#include<stdbool.h>
#include<stdlib.h>
#include<stdint.h>

typedef void (*TaskCallback)(void *arg);

// Async Task structure (opaque to users)
typedef struct AsyncTask AsyncTask;

// Async library structure (opaque to users)
typedef struct AsyncLib AsyncLib;

// Initialize and clean up the async library
AsyncLib *async_lib_init(void);
void async_lib_cleanup(AsyncLib *lib);

// Add a one-time or periodic task
AsyncTask *async_add_task(AsyncLib *lib, TaskCallback cb, void *arg, uint64_t delay_ms, bool periodic);

// Remove a task
bool async_remove_task(AsyncLib *lib, AsyncTask *task);

// Run the event loop
void async_run(AsyncLib *lib);

// Stop the event loop
void async_stop(AsyncLib *lib);


#endif //CUSTOM_ASYNC_H
