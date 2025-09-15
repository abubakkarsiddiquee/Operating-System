#include "scheduler.h"
#include <iostream>

/**
 * Shortest Job First (SJF) Scheduler
 * 
 * Algorithm: Execute the process with the shortest burst time among ready processes
 * - Non-preemptive
 * - Optimal for minimizing average waiting time
 * - Can cause starvation for long processes
 * 
 * TODO: Implement the schedule() function
 * HINT: At each scheduling decision, pick the shortest job among ready processes
 */
class SJFScheduler : public Scheduler {
public:
    SJFScheduler() : Scheduler("Shortest Job First (SJF)") {}
    
    void schedule() override {
        std::cout << "Starting SJF scheduling...\n";
        
        // TODO: Implement SJF scheduling algorithm
        // 
        // Steps to implement:
        // 1. While not all processes are complete:
        //    a. Get all ready processes at current time using get_ready_processes(current_time)
        //    b. If no ready processes, advance time to next arrival
        //    c. Find the process with shortest burst time among ready processes
        //    d. Run that process completely
        // 
        // Use these helper functions:
        // - all_processes_complete() - check if simulation is done
        // - get_ready_processes(time) - get processes that have arrived
        // - find next arrival time for advancing time when no process is ready
        // - run_process(pid, duration) - to execute a process
        // 
        // Example structure:
        // while (!all_processes_complete()) {
        //     if no ready process found:
        //         // Find next arrival time and advance
        //     else:
        //         // Find shortest job among ready processes
        //         // Run it completely
        //     }
        // }
        
        std::cout << "SJF scheduling completed.\n";
    }
};
