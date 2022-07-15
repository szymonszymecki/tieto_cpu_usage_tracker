#ifndef TRACKER_DATA_H
#define TRACKER_DATA_H

#include <threads.h>

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
} proc_stats;

/**
 * @brief Data which contain variables used between threads.
 * 
 */
typedef struct tracker_data {
    mtx_t tracker_mutex;
    size_t lines;           /**< Number of read statistics: number of cpu cores and additional line for summarized usage */
    proc_stats stats[];
} tracker_data;

/**
 * @brief Data initializer.
 * Function allocates needed memory space, initializes threads' mutex and extracts information about the number of cpu cores used by the system.
 * It will be used to provide information between threads.
 * 
 * @return Pointer to the program data
 */
tracker_data* tracker_data_init(void);

/**
 * @brief Data destructor.
 * Funtion frees allocated memory.
 * 
 */
void tracker_data_destroy(tracker_data*);

#endif