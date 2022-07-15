#include "tracker_data.h"

#include <stdlib.h>
#include <sys/sysinfo.h>

tracker_data* tracker_data_init(void) {
    const size_t processor_cores_count = get_nprocs_conf();
    const size_t data_lines = processor_cores_count + 1;

    tracker_data* new_tracker_data = malloc(sizeof(tracker_data) + sizeof(proc_stats) * (data_lines));
    new_tracker_data->lines = data_lines;


    mtx_init(&new_tracker_data->tracker_mutex, mtx_plain);

    return new_tracker_data;
}

void tracker_data_destroy(tracker_data* tracker_data) {
    mtx_destroy(&tracker_data->tracker_mutex);
    free(tracker_data);
    tracker_data = NULL;
}