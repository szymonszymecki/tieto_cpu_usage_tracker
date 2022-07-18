#ifndef TRACKER_DATA_H
#define TRACKER_DATA_H

#include "circular_buffer/circular_buffer.h"

#include <threads.h>
#include <signal.h>

extern volatile sig_atomic_t finished; /**< Condition for program to finish its work */

/**
 * @brief Statistics read from /proc/stat file about processor usage.
 * 
 */
typedef struct proc_stats {
    char stat_name[8];
    unsigned long stat_user;
    unsigned long stat_nice;
    unsigned long stat_system;
    unsigned long stat_idle;
    unsigned long stat_iowait;
    unsigned long stat_irq;
    unsigned long stat_softirq;
    unsigned long stat_steal;
    unsigned long stat_guest;
    unsigned long stat_guest_nice;
    double stat_percentage;
} proc_stats;

/**
 * @brief Data which contain variables used between threads.
 * 
 */
typedef struct tracker_data {
    mtx_t tracker_mutex;
    cnd_t cnd_analyze;
    cnd_t cnd_print;
    cnd_t cnd_watchdog;
    cnd_t cnd_log;
    size_t seconds;                 /**< Number of seconds since program beginning */
    size_t max_time;                /**< Time after which program finishes its work. */
    circular_buffer* circ_buffer;   /**< Buffer for logs */
    size_t lines;                   /**< Number of read statistics: number of cpu cores and additional line for averaged usage */
    proc_stats stats[];             /**< Array of stats for each core at current second */
} tracker_data;

/**
 * @brief Data initializer.
 * Function allocates needed memory space, initializes threads' mutex, conditional variables and extracts information about the number of cpu cores used by the system.
 * It will be used to provide information between threads.
 * 
 * @param max_time Time after which program finishes its work. If equals 0, it's set to @a INT_MAX value.
 * 
 * @return Pointer to the program data
 */
tracker_data* tracker_data_init(size_t max_time);

/**
 * @brief Data destructor.
 * Funtion frees allocated memory.
 * 
 * @param tracker_data Data to be destroyed.
 */
void tracker_data_destroy(tracker_data* tracker_data);

void term(int signum);

#endif