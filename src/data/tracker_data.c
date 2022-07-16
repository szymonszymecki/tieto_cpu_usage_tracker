#include "tracker_data.h"

#include <stdlib.h>
#include <sys/sysinfo.h>
#include <string.h>

tracker_data* tracker_data_init(void) {
    const size_t data_lines = get_nprocs_conf() + 1;

    tracker_data* new_tracker_data = malloc(sizeof(tracker_data) + sizeof(proc_stats) * (data_lines));
    new_tracker_data->lines = data_lines;
    new_tracker_data->finished = false;
    memset(new_tracker_data->stats, 0, data_lines * sizeof(new_tracker_data->stats[0]));

    mtx_init(&new_tracker_data->tracker_mutex, mtx_plain);
    cnd_init(&new_tracker_data->cnd_analyze);
    cnd_init(&new_tracker_data->cnd_print);

    return new_tracker_data;
}

void tracker_data_destroy(tracker_data* tracker_data) {
    cnd_destroy(&tracker_data->cnd_analyze);
    cnd_destroy(&tracker_data->cnd_print);
    mtx_destroy(&tracker_data->tracker_mutex);

    free(tracker_data);
    tracker_data = NULL;
}