#ifndef THREAD_READER_H
#define THREAD_READER_H

/**
 * @brief Reads statistics from /proc/stat file for further analyze.
 * 
 * @param new_data Data shared between threads.
 * 
 * @return Thread returns 0 when thread finishes its work. 
 */
int thread_read(void* new_data);

#endif