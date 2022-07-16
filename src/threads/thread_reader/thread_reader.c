#include "thread_reader.h"

#include "../../data/tracker_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int thread_read(void* new_data) {
    tracker_data* restrict data = new_data;

    do {
        FILE* stat_reader = fopen("/proc/stat", "r");
        if (!stat_reader) {
            perror("Reading stats from /proc/stat failed\n");
            goto FINISH;
        }

        mtx_lock(&data->tracker_mutex);
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
                perror("End of file reached in reader thread\n");
                data->finished = true;
                break;
            }
        }
        cnd_signal(&data->cnd_analyze);
        mtx_unlock(&data->tracker_mutex);

        fclose(stat_reader);
        sleep(1);
    } while (!data->finished);

    FINISH:
    data->finished = true;
    return 0;
}