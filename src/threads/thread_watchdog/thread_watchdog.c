#include "thread_watchdog.h"

#include "../../data/tracker_data.h"

#include <time.h>
#include <stdio.h>

int thread_watch(void* new_data) {
    tracker_data* restrict data = new_data;

    mtx_lock(&data->tracker_mutex);
    while (!data->finished) {

        struct timespec now;
        timespec_get(&now, TIME_UTC);
        now.tv_sec += 2;
        int timedwait_result = cnd_timedwait(&data->cnd_print, &data->tracker_mutex, &now);

        if (timedwait_result == thrd_timedout) {
            data->finished = true;
            cnd_signal(&data->cnd_log);
            cnd_signal(&data->cnd_analyze);
            cnd_signal(&data->cnd_print);
        }
    }
    mtx_unlock(&data->tracker_mutex);

    return 0;
}