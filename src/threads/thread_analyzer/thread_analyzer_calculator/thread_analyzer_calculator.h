#ifndef THREAD_ANALYZER_CALCULATOR_H
#define THREAD_ANALYZER_CALCULATOR_H

#include "../../../data/tracker_data.h"

/**
 * @brief Get the percentage usage of cpu
 * 
 * @param prev Statistics taken previous time from the reader.
 * @param next The newest statistics.
 * 
 * @return Percentage usage of cpu 
 */
double get_percentage(proc_stats prev, proc_stats next);

#endif