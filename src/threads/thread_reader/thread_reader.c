#include "thread_reader.h"

#include "../../data/tracker_data.h"

#include <stdio.h>
#include <stdlib.h>


int thread_read(void* new_data) {
    tracker_data* restrict data = new_data;

    FILE* stat_reader = fopen("/proc/stat", "r");
    if (!stat_reader) {
        perror("Reading stats from /proc/stat failed\n");
        return 1;
    }

    for (size_t line = 0; line < data->lines; ++line) {
        fscanf(stat_reader, "%8s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", data->stats[line].stat_name, &data->stats[line].stat_user,
            &data->stats[line].stat_nice, &data->stats[line].stat_system, &data->stats[line].stat_idle, &data->stats[line].stat_iowait, 
            &data->stats[line].stat_irq, &data->stats[line].stat_softirq, &data->stats[line].stat_steal, &data->stats[line].stat_guest,
            &data->stats[line].stat_guest_nice
        );
        
        printf("%8s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu\n", data->stats[line].stat_name, data->stats[line].stat_user,
            data->stats[line].stat_nice, data->stats[line].stat_system, data->stats[line].stat_idle, data->stats[line].stat_iowait, 
            data->stats[line].stat_irq, data->stats[line].stat_softirq, data->stats[line].stat_steal, data->stats[line].stat_guest,
            data->stats[line].stat_guest_nice
        );
    }

    fclose(stat_reader);
    return 0;
}