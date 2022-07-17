#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

/**
 * @brief Initializes all threads and waits for them to be joined.
 * 
 * @param new_data Data that will be shared between threads.
 */
void task_initialize(void* new_data);

#endif