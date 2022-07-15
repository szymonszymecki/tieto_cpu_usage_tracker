#include "thread_analyzer.h"

#include "../../data/tracker_data.h"

int thread_analyze(void* new_data) {
    tracker_data* restrict data = new_data;
    
    return data->lines;
}