#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include "process.h"
#include "gantt_chart.h"
#include <vector>

/**
 * Performance metrics for CPU scheduling algorithms
 * Students need to implement the calculation functions
 */
class PerformanceMetrics {
private:
    std::vector<Process> processes;
    GanttChart gantt;
    
public:
    // Constructor
    PerformanceMetrics(const std::vector<Process>& procs, const GanttChart& chart);
    
    // Basic metrics (students implement these)
    double calculate_average_turnaround_time() const;
    double calculate_average_waiting_time() const;
    double calculate_average_response_time() const;
    double calculate_cpu_utilization() const;
    double calculate_throughput() const;  // Processes per unit time
    
    // Advanced metrics (bonus - optional for students)
    double calculate_fairness_index() const;  // How fair is the scheduling?
    int calculate_context_switches() const;   // Number of process switches
    
    // Display functions
    void print_summary() const;
    void print_detailed() const;
    void print_process_metrics() const;
    
    // Helper functions (provided to students)
    int get_total_time() const;
    int get_total_processes() const;
    
private:
    // Helper function for students to understand
    bool is_valid_metrics() const;  // Check if all processes have valid timing
};

#endif // PERFORMANCE_H
