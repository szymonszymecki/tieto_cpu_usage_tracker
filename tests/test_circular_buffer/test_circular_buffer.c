#include "test_circular_buffer.h"

#include "../../src/data/circular_buffer/circular_buffer.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define TEST_LOG_MESSAGE_SIZE 64

void test_circular_buffer() {
    puts("Test: Circular buffer implementation");
    circular_buffer* new_circ_buffer = circular_buffer_init();
    assert(new_circ_buffer != NULL);

    puts("Pushing elements (default capacity: 10)");
    for (size_t msg_line = 0; msg_line < circular_buffer_get_size(new_circ_buffer); ++msg_line) {
        char msg[TEST_LOG_MESSAGE_SIZE];
        sprintf(msg, "Message: %zu\n", msg_line);
        circular_buffer_push(new_circ_buffer, msg);
    }

    puts("Pushing elements passed. Adding 11th element:");
    char too_much_msg[TEST_LOG_MESSAGE_SIZE];
    size_t too_much_number = 11;
    sprintf(too_much_msg, "Message: %zu\n", too_much_number);
    circular_buffer_push(new_circ_buffer, too_much_msg);
    assert(circular_buffer_get_count(new_circ_buffer) == 10);
    
    puts("Passed. Popping elements:");
    while (!circular_buffer_is_empty(new_circ_buffer)) {
        const char* msg = circular_buffer_pop(new_circ_buffer);
        puts(msg);
    }

    puts("Passed. Attempt to pop from empty buffer");
    const char* empty_msg = circular_buffer_pop(new_circ_buffer);
    assert(empty_msg == NULL);

    puts("Passed. Destroying buffer.");
    circular_buffer_destroy(new_circ_buffer);
    puts("Buffer destroyed.\n");
}
