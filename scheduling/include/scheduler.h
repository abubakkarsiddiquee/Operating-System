#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include "gantt_chart.h"
#include <vector>
#include <string>

/**
 * Abstract base class for all scheduling algorithms
 * Students will inherit from this class to implement specific algorithms
 */
class Scheduler {
protected:
    std::vector<Process> processes;
    std::vector<Process> original_processes;  // Keep original for reset
    GanttChart gantt;
    int current_time;
    std::string algorithm_name;

public:
    // Constructor
    Scheduler(const std::string& name);
    
    // Virtual destructor
    virtual ~Scheduler() = default;
    
    // Pure virtual function - students must implement this
    virtual void schedule() = 0;
    
    // Common functionality provided to students
    void load_processes(const std::vector<Process>& procs);
    void reset_simulation();
    void print_results() const;
    void print_gantt_chart() const;
    
    // Getters
    const std::vector<Process>& get_processes() const;
    const GanttChart& get_gantt_chart() const;
    std::string get_algorithm_name() const;
    
protected:
    // Helper functions for students to use
    void run_process(int pid, int duration);
    void add_to_gantt(int pid, int start_time, int end_time);
    bool all_processes_complete() const;
    std::vector<Process*> get_ready_processes(int time);
    Process* find_process_by_pid(int pid);
    void advance_time(int new_time);
    
    // Utility functions
    void sort_by_arrival_time();
    void sort_by_burst_time();
    void sort_by_priority();
    void sort_by_remaining_time();
};

/**
 * Factory function to create scheduler instances
 * Students don't need to modify this
 */
Scheduler* create_scheduler(const std::string& algorithm);

#endif // SCHEDULER_H
