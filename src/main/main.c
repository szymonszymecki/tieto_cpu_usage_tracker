#include "../data/tracker_data.h"
#include "../task_manager/task_manager.h"

#include <stdlib.h>

int main(void) {
    tracker_data* new_data = tracker_data_init();
    task_initialize(new_data);
    tracker_data_destroy(new_data);

    return EXIT_SUCCESS;
}