#ifndef THREAD_ANALYZER_H
#define THREAD_ANALYZER_H

/**
 * @brief Analyzes data received from printer and sends its results to the printer.
 * 
 * @param new_data Data shared between threads.
 * 
 * @return Thread returns 0 when thread finishes its work. 
 */
int thread_analyze(void* new_data);

#endif