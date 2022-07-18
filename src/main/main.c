#include "../data/tracker_data.h"
#include "../task_manager/task_manager.h"

#include <stdlib.h>

#define MAX_SECONDS 0

int main(void) {
    tracker_data* new_data = tracker_data_init(MAX_SECONDS);
    task_initialize(new_data);
    tracker_data_destroy(new_data);

    return EXIT_SUCCESS;
}