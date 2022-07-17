#include "../test_tracker_data_init/test_tracker_data_init.h"
#include "../test_circular_buffer/test_circular_buffer.h"

#include "../../src/data/tracker_data.h"
#include "../../src/task_manager/task_manager.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    test_tracker_data_init();
    test_circular_buffer();

    return EXIT_SUCCESS;
}