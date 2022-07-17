#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdlib.h>
#include <stdbool.h>

#define LOG_MESSAGE_SIZE 64
#define LOG_BUFFER_CAPACITY 10

/**
 * @brief Contains circular buffer for logs
 * 
 */
typedef struct circular_buffer circular_buffer;

/**
 * @brief Circular buffer initializer.
 * 
 * @return Pointer to the buffer
 */
circular_buffer* circular_buffer_init();

/**
 * @brief Log Buffer destructor.
 * 
 * @param circ_buffer Buffer that's being destroyed.
 */
void circular_buffer_destroy(circular_buffer* circ_buffer);

/**
 * @brief Adds new element to the buffer.
 * Function doesn't add anything if there's no space for new element.
 * 
 * @param circ_buffer Log buffer where new element is added.
 * @param item Message to be added.
 */
void circular_buffer_push(circular_buffer* circ_buffer, char* item);

/**
 * @brief Removes element from the buffer and stores is in the pointer.
 * 
 * @param circ_buffer Log buffer where an element is removed.
 * @return Pointer to the popped element passed in @param item or NULL if there is nothing to pop.
 */
const char* circular_buffer_pop(circular_buffer* circ_buffer);

/**
 * @brief Checks if the circular buffer is empty.
 * 
 * @param circ_buffer Log buffer that's being checked.
 */
bool circular_buffer_is_empty(circular_buffer* circ_buffer);

size_t circular_buffer_get_count(circular_buffer* circ_buffer);

size_t circular_buffer_get_size(circular_buffer* circ_buffer);

#endif