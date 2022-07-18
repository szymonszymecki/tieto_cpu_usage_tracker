#include "thread_reader.h"

#include "../../data/tracker_data.h"
#include "../thread_finisher/thread_finisher.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int thread_read(void* new_data) {
    tracker_data* restrict data = new_data;

    do {
        FILE* stat_reader = fopen("/proc/stat", "r");
        if (!stat_reader) {
            mtx_lock(&data->tracker_mutex);

            char msg[LOG_MESSAGE_SIZE];
            sprintf(msg, "READER (second %zu): Opening /proc/stat file failed", (data->seconds + 1));
            circular_buffer_push(data->circ_buffer, msg);
            goto FINISH;
        }

        mtx_lock(&data->tracker_mutex);
        data->seconds++;
        if (data->seconds > data->max_time) {
            goto FINISH;
        }
        for (size_t line = 0; line < data->lines; ++line) {
            if (fscanf(stat_reader, "%8s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
                data->stats[line].stat_name,
                &data->stats[line].stat_user,
                &data->stats[line].stat_nice,
                &data->stats[line].stat_system,
                &data->stats[line].stat_idle,
                &data->stats[line].stat_iowait, 
                &data->stats[line].stat_irq,
                &data->stats[line].stat_softirq,
                &data->stats[line].stat_steal,
                &data->stats[line].stat_guest,
                &data->stats[line].stat_guest_nice
            ) == EOF) {
                char msg[LOG_MESSAGE_SIZE];
                sprintf(msg, "READER (second %zu): End of file reached in reader thread.", data->seconds);
                circular_buffer_push(data->circ_buffer, msg);
                goto FINISH;
            }
        }

        if (!finished) {
            char msg[LOG_MESSAGE_SIZE];
            sprintf(msg, "READER (second %zu): Sending statistics to analyzer.", data->seconds);
            circular_buffer_push(data->circ_buffer, msg);
            cnd_signal(&data->cnd_log);
            cnd_signal(&data->cnd_analyze);
        }
        mtx_unlock(&data->tracker_mutex);

        fclose(stat_reader);
        thrd_sleep(&(struct timespec){.tv_sec = 1}, NULL);
    } while (!finished);

    mtx_lock(&data->tracker_mutex);
    FINISH:
    thread_finish(data);
    mtx_unlock(&data->tracker_mutex);
    return 0;
}