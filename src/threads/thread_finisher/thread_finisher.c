#include "thread_finisher.h"

#include "../../data/tracker_data.h"

void thread_finish(void* new_data) {
    tracker_data* restrict data = new_data;
    char* msg = "Threads finish their work.";
    circular_buffer_push(data->circ_buffer, msg);
    finished = 1;
    cnd_signal(&data->cnd_log);
    cnd_signal(&data->cnd_analyze);
    cnd_signal(&data->cnd_print);
    cnd_signal(&data->cnd_watchdog);
}