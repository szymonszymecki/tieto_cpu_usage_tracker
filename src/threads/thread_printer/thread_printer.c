#include "thread_printer.h"

#include "../../data/tracker_data.h"

#include <stdio.h>

int thread_print(void* new_data) {
    tracker_data* restrict data = new_data;

    mtx_lock(&data->tracker_mutex);
    while (!data->finished) {
        cnd_wait(&data->cnd_print, &data->tracker_mutex);

        if (!data->finished) {
            puts("\nNew data:");
            for (size_t line = 0; line < data->lines; ++line) {
                printf("%8s -> core usage (percentage): %f %%\n", data->stats[line].stat_name, data->stats[line].stat_percentage);
            }
        }
    }
    mtx_unlock(&data->tracker_mutex);
    
    return 0;
}