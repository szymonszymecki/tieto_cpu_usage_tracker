#include "thread_watchdog.h"

#include "../../data/tracker_data.h"
#include "../thread_finisher/thread_finisher.h"

#include <time.h>
#include <stdio.h>

int thread_watch(void* new_data) {
    tracker_data* restrict data = new_data;

    mtx_lock(&data->tracker_mutex);
    while (!data->finished) {

        struct timespec now;
        timespec_get(&now, TIME_UTC);
        now.tv_sec += 2;
        int timedwait_result = cnd_timedwait(&data->cnd_watchdog, &data->tracker_mutex, &now);
        
        if (!data->finished && (timedwait_result == thrd_timedout)) {
            char msg[LOG_MESSAGE_SIZE];
            sprintf(msg, "WATCHDOG (second %zu): Timeout occured.", data->seconds);
            circular_buffer_push(data->circ_buffer, msg);
            thread_finish(data);
        }
    }
    mtx_unlock(&data->tracker_mutex);

    return 0;
}