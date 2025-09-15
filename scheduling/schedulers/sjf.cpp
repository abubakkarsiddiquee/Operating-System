#include "scheduler.h"
#include <iostream>
#include <vector>
#include <algorithm>

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

        int current_time = 0;

        // Sort all processes by arrival time initially
        std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            return a.arrivalTime < b.arrivalTime;
        });

        while (!all_processes_complete()) {
            // get all arrived and not finished processes
            std::vector<Process*> ready = get_ready_processes(current_time);

            if (ready.empty()) {
                // find the next process arrival time and jump there
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
                // find the process with the smallest burst time
                Process* shortest = *std::min_element(ready.begin(), ready.end(),
                    [](Process* a, Process* b) {
                        return a->burstTime < b->burstTime;
                    });

                run_process(shortest->pid, shortest->burstTime); // run fully
                current_time += shortest->burstTime;

                shortest->remainingTime = 0;
                shortest->isComplete = true;
                shortest->finishTime = current_time;
                shortest->turnaroundTime = shortest->finishTime - shortest->arrivalTime;
                shortest->waitingTime = shortest->turnaroundTime - shortest->burstTime;
            }
        }

        std::cout << "SJF scheduling completed.\n";
    }
};
