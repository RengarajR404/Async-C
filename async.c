#include "async.h"
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

struct AsyncTask {
    TaskCallback callback;
    void *arg;
    uint64_t next_run; // Next run time in milliseconds
    uint64_t interval; // 0 for one-time tasks, >0 for periodic tasks
    bool active;       // Flag to indicate if the task is active
};

// Async library structure
struct AsyncLib {
    AsyncTask **tasks;
    size_t task_count;
    size_t capacity;    // Current capacity of the task array
    bool running;
};

static uint64_t current_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)(tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

AsyncLib *async_lib_init(void) {
    AsyncLib *lib = malloc(sizeof(AsyncLib));
    if (!lib) return NULL;

    lib->tasks = malloc(sizeof(AsyncTask *) * 10); // Initial capacity of 10 tasks
    if (!lib->tasks) {
        free(lib);
        return NULL;
    }

    lib->task_count = 0;
    lib->capacity = 10;  // Initial capacity
    lib->running = false;
    return lib;
}

void async_lib_cleanup(AsyncLib *lib) {
    if (!lib) return;

    for (size_t i = 0; i < lib->task_count; i++) {
        free(lib->tasks[i]);
    }
    free(lib->tasks);
    free(lib);
}

static void resize_task_array(AsyncLib *lib) {
    lib->capacity = lib->capacity + (lib->capacity / 2); // Increase capacity by 1.5x
    lib->tasks = realloc(lib->tasks, sizeof(AsyncTask *) * lib->capacity);
    if (!lib->tasks) {
        perror("Failed to resize task array");
        exit(1);
    }
}

AsyncTask *async_add_task(AsyncLib *lib, TaskCallback cb, void *arg, uint64_t delay_ms, bool periodic) {
    if (!lib || !cb) return NULL;

    if (lib->task_count == lib->capacity) {
        resize_task_array(lib);  // Resize the task array if full
    }

    AsyncTask *task = malloc(sizeof(AsyncTask));
    if (!task) return NULL;

    task->callback = cb;
    task->arg = arg;
    task->next_run = current_time_ms() + delay_ms;
    task->interval = periodic ? delay_ms : 0;
    task->active = true;

    lib->tasks[lib->task_count++] = task;
    return task;
}

bool async_remove_task(AsyncLib *lib, AsyncTask *task) {
    if (!lib || !task) return false;

    for (size_t i = 0; i < lib->task_count; i++) {
        if (lib->tasks[i] == task) {
            free(task);
            lib->tasks[i] = lib->tasks[--lib->task_count];
            return true;
        }
    }
    return false;
}

void async_run(AsyncLib *lib) {
    if (!lib) return;

    lib->running = true;

    while (lib->running) {
        uint64_t now = current_time_ms();

        for (size_t i = 0; i < lib->task_count; i++) {
            AsyncTask *task = lib->tasks[i];
            if (task->active && task->next_run <= now) {
                task->callback(task->arg);

                if (task->interval > 0) {
                    task->next_run = now + task->interval;
                } else {
                    task->active = false;
                }
            }
        }

        // Sleep for a short duration to avoid busy-waiting
        usleep(1000); // Sleep for 1ms
    }
}

void async_stop(AsyncLib *lib) {
    if (lib) lib->running = false;
}
