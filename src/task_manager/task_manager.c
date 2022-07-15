#include "task_manager.h"

#include "../data/tracker_data.h"

#include "../threads/thread_reader/thread_reader.h"
#include "../threads/thread_analyzer/thread_analyzer.h"
#include "../threads/thread_printer/thread_printer.h"

#include <threads.h>

#define THREADS_COUNT 3

void task_initialize(void* new_data) {
    // thrd_t thrds[THREADS_COUNT];
    
    tracker_data* restrict data = new_data;

    thread_read(data);
    
    // thrd_create(&thrds[0], thread_read, NULL);
    // thrd_create(&thrds[1], thread_analyze, NULL);
    // thrd_create(&thrds[2], thread_print, NULL);

    // for (size_t idx = 0; idx < THREADS_COUNT; ++idx) {
    //     thrd_join(thrds[idx], NULL);
    // }

    tracker_data_destroy(data);

}