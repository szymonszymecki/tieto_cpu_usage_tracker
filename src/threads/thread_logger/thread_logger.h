#ifndef THREAD_LOGGER_H
#define THREAD_LOGGER_H

/**
 * @brief Writes logs to the file.
 * 
 * @param new_data Data shared between threads.
 * 
 * @return Thread returns 0 when thread finishes its work. 
 */
int thread_log(void* new_data);

#endif