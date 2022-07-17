#include "thread_logger.h"

#include "../../data/tracker_data.h"

#include <stdio.h>

int thread_log(void* new_data) {
    tracker_data* restrict data = new_data;

    FILE* logger = fopen("../../logs.txt", "w");
    if (!logger) {
        perror("Opening logs.txt file failed\n");
    }

    mtx_lock(&data->tracker_mutex);
    while (!data->finished) {
        cnd_wait(&data->cnd_log, &data->tracker_mutex);

    }
    mtx_unlock(&data->tracker_mutex);

    fclose(logger);

    return 0;
}