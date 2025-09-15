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
        //Sort by arrival time
         std::sort(processes.begin(), processes.end(),
                  [](const Process &a, const Process &b) {
                      return a.arrivalTime < b.arrivalTime;
                  });

        int currentTime = 0;

        for (auto &p : processes) {
            if (currentTime < p.arrivalTime)
                currentTime = p.arrivalTime; // wait until process arrives

            p.startTime = currentTime;
            p.finishTime = currentTime + p.burstTime;
            p.turnaroundTime = p.finishTime - p.arrivalTime;
            p.waitingTime = p.startTime - p.arrivalTime;

            currentTime += p.burstTime;

            std::cout << "Process " << p.pid
                      << " | Start: " << p.startTime
                      << " | Finish: " << p.finishTime
                      << " | Waiting: " << p.waitingTime
                      << " | Turnaround: " << p.turnaroundTime << "\n";
        }
        
        std::cout << "FCFS scheduling completed.\n";
    }
};
