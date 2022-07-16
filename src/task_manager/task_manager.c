#include "task_manager.h"

#include "../data/tracker_data.h"

#include "../threads/thread_reader/thread_reader.h"
#include "../threads/thread_analyzer/thread_analyzer.h"
#include "../threads/thread_printer/thread_printer.h"

#include <threads.h>

#define THREADS_COUNT 3

void task_initialize(void* new_data) {
    thrd_t thrds[THREADS_COUNT];

    tracker_data* restrict data = new_data;
    
    thrd_create(&thrds[0], thread_read, data);
    thrd_create(&thrds[1], thread_analyze, data);
    thrd_create(&thrds[2], thread_print, data);

    for (size_t thrd_count = 0; thrd_count < THREADS_COUNT; ++thrd_count) {
        thrd_join(thrds[thrd_count], NULL);
    }

}