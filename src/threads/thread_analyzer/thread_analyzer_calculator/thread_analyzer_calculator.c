#include "thread_analyzer_calculator.h"

double get_percentage(proc_stats prev, proc_stats next) {
    unsigned long prev_idle = prev.stat_idle + prev.stat_iowait;
    unsigned long idle = next.stat_idle + next.stat_iowait;

    unsigned long prev_non_idle = prev.stat_user + prev.stat_nice + prev.stat_system + prev.stat_irq + prev.stat_softirq + prev.stat_steal;
    unsigned long non_idle = next.stat_user + next.stat_nice + next.stat_system + next.stat_irq + next.stat_softirq + next.stat_steal;

    unsigned long prev_total = prev_idle + prev_non_idle;
    unsigned long total = idle + non_idle;

    unsigned long totald = total - prev_total;
    unsigned long idled = idle - prev_idle;

    return 100.0 * (totald - idled) / totald;
}