#include "circular_buffer.h"

#include <string.h>
#include <stdio.h>

struct circular_buffer {
    char* element[LOG_BUFFER_CAPACITY]; /**< Data buffer (array of strings) */
    size_t start;                       /**< Index of first element to be popped */
    size_t count;                       /**< Index of recently added element */
    size_t size;                        /**< Maximum number of items in the buffer */
};

circular_buffer* circular_buffer_init() {
    circular_buffer* circ_buffer = malloc(sizeof(circular_buffer));
    circ_buffer->start = 0;
    circ_buffer->count = 0;
    circ_buffer->size = LOG_BUFFER_CAPACITY;

    for (size_t msg_idx = 0; msg_idx < circ_buffer->size; ++msg_idx) {
        circ_buffer->element[msg_idx] = malloc(sizeof(circ_buffer->element[msg_idx][0]) * LOG_MESSAGE_SIZE);
        memset(circ_buffer->element[msg_idx], 0, sizeof(circ_buffer->element[msg_idx][0]) * LOG_MESSAGE_SIZE);

        if (circ_buffer->element[msg_idx] == NULL) {
            perror("Unable to initialize circular buffer");
            return NULL;
        }
    }

    return circ_buffer;
}

void circular_buffer_destroy(circular_buffer* circ_buffer) {
    for (size_t msg_idx = 0; msg_idx < circ_buffer->size; ++msg_idx) {
        free(circ_buffer->element[msg_idx]);
        circ_buffer->element[msg_idx] = NULL;
    }
    free(circ_buffer);
    circ_buffer = NULL;
}

void circular_buffer_push(circular_buffer* circ_buffer, char* item) {
    size_t index;
    if (circ_buffer->count == circ_buffer->size) {
        perror("There's too many items in a buffer to add new item.");
        return;
    }

    index = (circ_buffer->start + circ_buffer->count) % circ_buffer->size;
    ++circ_buffer->count;
    memcpy(circ_buffer->element[index], item, LOG_MESSAGE_SIZE);
}

const char* circular_buffer_pop(circular_buffer* circ_buffer) {
    if (circ_buffer->count == 0) {
        perror("There's no items in a buffer.");
        return NULL;
    }
    
    const char* popped_item = circ_buffer->element[circ_buffer->start];
    ++circ_buffer->start;
    --circ_buffer->count;
    if (circ_buffer->start == circ_buffer->size) {
        circ_buffer->start = 0;
    }
    
    return popped_item;
}

bool circular_buffer_is_empty(circular_buffer* circ_buffer) {
    return (circ_buffer->count == 0);
}

size_t circular_buffer_get_count(circular_buffer* circ_buffer) {
    return circ_buffer->count;
}

size_t circular_buffer_get_size(circular_buffer* circ_buffer) {
    return circ_buffer->size;
}