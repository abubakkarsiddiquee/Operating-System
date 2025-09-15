#include "scheduler.h"
#include <iostream>
#include <vector>
#include <algorithm>

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

        int current_time = 0;

        while (!all_processes_complete()) {
            // get all ready processes at current time
            std::vector<Process*> ready = get_ready_processes(current_time);

            if (ready.empty()) {
                // if nothing is ready, jump to next arrival
                int next_arrival = INT_MAX;
                for (auto &p : processes) {
                    if (!p.isComplete && p.arrivalTime > current_time) {
                        next_arrival = std::min(next_arrival, p.arrivalTime);
                    }
                }
                if (next_arrival != INT_MAX) {
                    current_time = next_arrival;
                }
            } else {
                // choose process with shortest remaining time
                Process* shortest = *std::min_element(ready.begin(), ready.end(),
                    [](Process* a, Process* b) {
                        return a->remainingTime < b->remainingTime;
                    });

                // run it for 1 unit (preemptive checking)
                run_process(shortest->pid, 1);
                current_time++;
                shortest->remainingTime--;

                // if done, mark complete
                if (shortest->remainingTime == 0) {
                    shortest->isComplete = true;
                    shortest->finishTime = current_time;
                    shortest->turnaroundTime = shortest->finishTime - shortest->arrivalTime;
                    shortest->waitingTime = shortest->turnaroundTime - shortest->burstTime;
                }
            }
        }

        std::cout << "STCF scheduling completed.\n";
    }
};
