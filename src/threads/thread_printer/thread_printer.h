#ifndef THREAD_PRINTER_H
#define THREAD_PRINTER_H

/**
 * @brief Prints percentage cpu usage on terminal for each core (and average for all cores).
 * 
 * @return Thread returns 0 when thread finishes its work.
 */
int thread_print(void* new_data);

#endif