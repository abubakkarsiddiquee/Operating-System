#include "scheduler.h"
#include <iostream>

/**
 * First Come First Serve (FCFS) Scheduler
 * Also known as First In First Out (FIFO)
 * 
 * Algorithm: Execute processes in the order they arrive
 * - Non-preemptive
 * - Simple queue-based scheduling
 * 
 * TODO: Implement the schedule() function
 * HINT: Sort processes by arrival time, then execute each completely
 */
class FCFSScheduler : public Scheduler {
public:
    FCFSScheduler() : Scheduler("First Come First Serve (FCFS)") {}
    
    void schedule() override {
        std::cout << "Starting FCFS scheduling...\n";
        
        // EXAMPLE IMPLEMENTATION [Demo in class]
        
        std::cout << "FCFS scheduling completed.\n";
    }
};
