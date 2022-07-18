#define _XOPEN_SOURCE 700

#include "tracker_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

volatile sig_atomic_t finished = 0;

tracker_data* tracker_data_init(size_t max_time) {
    const size_t data_lines = get_nprocs_conf() + 1;

    tracker_data* new_tracker_data = malloc(sizeof(tracker_data) + sizeof(proc_stats) * (data_lines));
    if (new_tracker_data == NULL) {
        perror("Unable to initialize new tracker data");
        return NULL;
    }

    new_tracker_data->lines = data_lines;
    new_tracker_data->seconds = 0;
    new_tracker_data->max_time = (max_time != 0) ? max_time : INT_MAX;
    memset(new_tracker_data->stats, 0, data_lines * sizeof(new_tracker_data->stats[0]));
    
    new_tracker_data->circ_buffer = circular_buffer_init();
    mtx_init(&new_tracker_data->tracker_mutex, mtx_plain);
    cnd_init(&new_tracker_data->cnd_analyze);
    cnd_init(&new_tracker_data->cnd_print);
    cnd_init(&new_tracker_data->cnd_watchdog);
    cnd_init(&new_tracker_data->cnd_log);

    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);

    return new_tracker_data;
}

void tracker_data_destroy(tracker_data* tracker_data) {
    circular_buffer_destroy(tracker_data->circ_buffer);
    cnd_destroy(&tracker_data->cnd_analyze);
    cnd_destroy(&tracker_data->cnd_print);
    cnd_destroy(&tracker_data->cnd_watchdog);
    cnd_destroy(&tracker_data->cnd_log);
    mtx_destroy(&tracker_data->tracker_mutex);

    free(tracker_data);
    tracker_data = NULL;
}

void term(int signum) {
    finished = signum;
}