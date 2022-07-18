#ifndef THREAD_FINISHER_H
#define THREAD_FINISHER_H

/**
 * @brief Sets @a finished flag to @a true and allows threads to finish their work.
 * 
 * @param new_data Data shared between threads, contain conditional variables needed to be signaled.
 */
void thread_finish(void* new_data);

#endif