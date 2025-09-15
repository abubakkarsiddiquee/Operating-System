#include "scheduler.h"
#include <iostream>

/**
 * Shortest Time to Completion First (STCF) Scheduler
 * Also known as Shortest Remaining Time First (SRTF)
 * 
 * Algorithm: Always execute the process with the shortest remaining time
 * - Preemptive version of SJF
 * - Optimal for minimizing average turnaround time
 * - Requires frequent preemption checks
 * 
 * TODO: Implement the schedule() function
 * HINT: Check at each time unit if a better (shorter) process becomes available
 */
class STCFScheduler : public Scheduler {
public:
    STCFScheduler() : Scheduler("Shortest Time to Completion First (STCF)") {}
    
    void schedule() override {
        std::cout << "Starting STCF scheduling...\n";
        
        // TODO: Implement STCF scheduling algorithm
        // 
        // Steps to implement:
        // 1. While not all processes are complete:
        //    a. Get all ready processes at current time
        //    b. If no ready processes, advance time to next arrival
        //    c. Find process with shortest remaining time among ready processes
        //    d. Run it for until preemption is needed
        //    e. Check if a new process with shorter remaining time has arrived
        // 
        // Use these helper functions:
        // - all_processes_complete() - check if simulation is done
        // - get_ready_processes(time) - get processes that have arrived
        // - run_process(pid, 1) - run process for 1 time unit
        // - Process.remaining_time - to compare remaining times
        // 
        // Example structure:
        // while (!all_processes_complete()) {
        //     if no ready process found:
        //         // Find next arrival and advance time
        //     else:
        //         // Find process with shortest remaining time
        //         // Run until preemption is needed
        //         // Run current process until that time or completion
        //     }
        // }
        //
        
        std::cout << "STCF scheduling completed.\n";
    }
};
