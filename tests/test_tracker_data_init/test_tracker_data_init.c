#include "test_tracker_data_init.h"

#include "../../src/data/tracker_data.h"

#include <stdio.h>
#include <assert.h>
#include <sys/sysinfo.h>

void test_tracker_data_init() {
    puts("Test: Data initialization");
    tracker_data* new_data = tracker_data_init(0);
    assert(new_data != NULL);
    puts("Data initialization: Passed. Checking cores count (expected 4).");
    assert(get_nprocs_conf() == 4);
    puts("Number of cpu cores correct. Destroying new data.");
    tracker_data_destroy(new_data);
    puts("Data destroyed.\n");
}