#include "thread_analyzer.h"

#include "../../data/tracker_data.h"
#include "thread_analyzer_calculator/thread_analyzer_calculator.h"

#include <string.h>
#include <stdio.h>

int thread_analyze(void* new_data) {
    tracker_data* restrict data = new_data;

    proc_stats prev[data->lines];
    memset(prev, 0, data->lines * sizeof(prev[0]));

    while (!data->finished) {
        mtx_lock(&data->tracker_mutex);
        cnd_wait(&data->cnd_analyze, &data->tracker_mutex);

        if (!data->finished) {
            for (size_t line = 0; line < data->lines; ++line) {
                data->stats[line].stat_percentage = get_percentage(prev[line], data->stats[line]);
                
                // saves data for new statistics from reader.
                prev[line].stat_user = data->stats[line].stat_user;
                prev[line].stat_nice = data->stats[line].stat_nice;
                prev[line].stat_system = data->stats[line].stat_system;
                prev[line].stat_idle = data->stats[line].stat_idle;
                prev[line].stat_iowait = data->stats[line].stat_iowait;
                prev[line].stat_irq = data->stats[line].stat_irq;
                prev[line].stat_softirq = data->stats[line].stat_softirq;
                prev[line].stat_steal = data->stats[line].stat_steal;
            }
            cnd_signal(&data->cnd_print);
        }

        mtx_unlock(&data->tracker_mutex);
    }
    
    return 0;
}