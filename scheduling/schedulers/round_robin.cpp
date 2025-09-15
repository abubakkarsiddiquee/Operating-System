#include "scheduler.h"
#include <iostream>
#include <queue>

/**
 * Round Robin (RR) Scheduler
 * 
 * Algorithm: Give each process a fixed time slice (quantum) in circular order
 * - Preemptive
 * - Fair scheduling - no starvation
 * - Performance depends on time quantum size
 * 
 * TODO: Implement the schedule() function
 * HINT: Use a queue to maintain ready processes and rotate them
 */
class RoundRobinScheduler : public Scheduler {
private:
    int time_quantum;  // Time slice for each process
    
public:
    RoundRobinScheduler(int quantum = 2) : Scheduler("Round Robin (RR)"), time_quantum(quantum) {}
    
    void schedule() override {
        std::cout << "Starting Round Robin scheduling with time quantum = " 
                  << time_quantum << "...\n";
        
        // TODO: Implement Round Robin scheduling algorithm
        // 
        // Steps to implement:
        // 1. Use a queue to maintain ready processes
        // 2. While not all processes are complete:
        //    a. Add newly arrived processes to the ready queue
        //    b. If queue is empty, advance time to next arrival
        //    c. Take process from front of queue
        //    d. Run it for min(time_quantum, remaining_time)
        //    e. If process not complete, add it back to queue
        // 
        // Use these helper functions:
        // - all_processes_complete() - check if simulation is done
        // - run_process(pid, duration) - to execute a process
        // - std::queue<Process*> for ready queue management
        // 
        // Example structure:
        // std::queue<Process*> ready_queue;
        // while (!all_processes_complete()) {
        //     // Add newly arrived processes to queue
        //     if no ready process is in queue:
        //         // Advance time to next arrival
        //     else:
        //         // Pop process from front of queue, run it, and requeue if needed
        // }

        std::queue<Process*> ready_queue;
        int current_time = 0;

        // Sort by arrival time to track when they come
        std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            return a.arrivalTime < b.arrivalTime;
        });

        size_t index = 0; // to track which process will arrive next

        while (!all_processes_complete()) {

            // Add newly arrived processes to ready queue
            while (index < processes.size() && processes[index].arrivalTime <= current_time) {
                ready_queue.push(&processes[index]);
                index++;
            }

            if (ready_queue.empty()) {
                // no process is ready → jump to next arrival
                if (index < processes.size()) {
                    current_time = processes[index].arrivalTime;
                    continue;
                }
            } else {
                Process* p = ready_queue.front();
                ready_queue.pop();

                int run_time = std::min(time_quantum, p->remainingTime);

                run_process(p->pid, run_time); // provided helper
                current_time += run_time;
                p->remainingTime -= run_time;

                // add new arrivals that came during this run
                while (index < processes.size() && processes[index].arrivalTime <= current_time) {
                    ready_queue.push(&processes[index]);
                    index++;
                }

                // if process still not finished → put it back
                if (p->remainingTime > 0) {
                    ready_queue.push(p);
                } else {
                    p->finishTime = current_time;
                    p->turnaroundTime = p->finishTime - p->arrivalTime;
                    p->waitingTime = p->turnaroundTime - p->burstTime;
                }
            }
        }

        std::cout << "Round Robin scheduling completed.\n";
    }
    
    // Allow setting different time quantum for testing
    void set_time_quantum(int quantum) {
        if (quantum > 0) {
            time_quantum = quantum;
        }
    }
};
