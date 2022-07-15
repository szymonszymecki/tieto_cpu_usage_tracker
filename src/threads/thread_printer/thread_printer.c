#include "thread_printer.h"

#include "../../data/tracker_data.h"

int thread_print(void* new_data) {
    tracker_data* restrict data = new_data;
    
    return data->lines;
}