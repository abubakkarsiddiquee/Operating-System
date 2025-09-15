#ifndef PROCESS_H
#define PROCESS_H

#include <string>

/**
 * Represents a process in the CPU scheduling simulation
 */
class Process {
public:
    // Process identification
    int pid;                    // Process ID
    std::string name;          // Process name (optional)
    
    // Timing information
    int arrival_time;          // When process arrives in the system
    int burst_time;            // Total CPU time needed
    int remaining_time;        // Remaining CPU time (for preemptive algorithms)
    int priority;              // Process priority (lower number = higher priority)
    
    // Scheduling results (filled during simulation)
    int start_time;            // When process first gets CPU
    int completion_time;       // When process finishes
    int waiting_time;          // Total time spent waiting
    int turnaround_time;       // completion_time - arrival_time
    int response_time;         // start_time - arrival_time
    
    // State tracking
    bool has_started;          // Has the process started execution?
    int last_run_time;         // Last time this process ran (for time slice tracking)
    
    // Constructor
    Process(int pid, int arrival, int burst, int priority = 0, const std::string& name = "");
    
    // Copy constructor
    Process(const Process& other);
    
    // Assignment operator
    Process& operator=(const Process& other);
    
    // Utility functions
    bool is_complete() const;
    void reset_for_simulation();  // Reset timing fields for new simulation
    void calculate_metrics();     // Calculate turnaround, waiting, response times
    
    // Display functions
    std::string to_string() const;
    void print_details() const;
    
    // Comparison operators (useful for sorting)
    bool operator<(const Process& other) const;  // Compare by arrival time
};

#endif // PROCESS_H
