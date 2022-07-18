#include "thread_logger.h"

#include "../../data/tracker_data.h"
#include "../thread_finisher/thread_finisher.h"

#include <stdio.h>

int thread_log(void* new_data) {
    tracker_data* restrict data = new_data;

    FILE* logger = fopen("logs.txt", "w");
    if (!logger) {
        perror("Opening logs.txt file failed");
        thread_finish(data);
        return 0;
    }

    mtx_lock(&data->tracker_mutex);
    while (!finished) {
        cnd_wait(&data->cnd_log, &data->tracker_mutex);

        while (!circular_buffer_is_empty(data->circ_buffer)) {
            const char* msg = circular_buffer_pop(data->circ_buffer);
            fputs(msg, logger);
            fputs("\n", logger);
        }
        fflush(logger);
        cnd_signal(&data->cnd_watchdog);
    }
    mtx_unlock(&data->tracker_mutex);

    fclose(logger);

    return 0;
}