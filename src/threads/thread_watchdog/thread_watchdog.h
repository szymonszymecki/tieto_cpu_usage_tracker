#ifndef THREAD_WATCHDOG_H
#define THREAD_WATCHDOG_H

/**
 * @brief Checks if each thread works properly.
 * 
 * @return Thread returns 0 when thread finishes its work. 
 */
int thread_watch(void*);

#endif