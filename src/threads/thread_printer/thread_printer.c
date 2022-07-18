#include "thread_printer.h"

#include "../../data/tracker_data.h"

#include <stdio.h>

int thread_print(void* new_data) {
    tracker_data* restrict data = new_data;

    mtx_lock(&data->tracker_mutex);
    while (!finished) {
        cnd_wait(&data->cnd_print, &data->tracker_mutex);
        
        if (!finished) {
            puts("\nNew data:");
            for (size_t line = 0; line < data->lines; ++line) {
                printf("%8s -> core usage (percentage): %f %%\n", data->stats[line].stat_name, data->stats[line].stat_percentage);
            }
            
            char msg[LOG_MESSAGE_SIZE];
            sprintf(msg, "PRINTER (second %zu): Printing statistics on the console.", data->seconds);
            circular_buffer_push(data->circ_buffer, msg);
            cnd_signal(&data->cnd_log);
        }
    }
    mtx_unlock(&data->tracker_mutex);
    
    return 0;
}