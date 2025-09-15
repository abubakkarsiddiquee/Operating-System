#include "scheduler.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

// Include all scheduler implementations
#include "../schedulers/fcfs.cpp"
#include "../schedulers/sjf.cpp"
#include "../schedulers/stcf.cpp"
#include "../schedulers/round_robin.cpp"

#include <iomanip>

Scheduler::Scheduler(const std::string& name) 
    : current_time(0), algorithm_name(name) {}

void Scheduler::load_processes(const std::vector<Process>& procs) {
    processes = procs;
    original_processes = procs;  // Keep a copy for reset
    
    // Reset all processes for simulation
    for (auto& process : processes) {
        process.reset_for_simulation();
    }
}

void Scheduler::reset_simulation() {
    processes = original_processes;
    for (auto& process : processes) {
        process.reset_for_simulation();
    }
    gantt.clear();
    current_time = 0;
}

void Scheduler::print_results() const {
    std::cout << "\n=== " << algorithm_name << " Scheduling Results ===\n\n";
    
    // Print individual process results
    std::cout << "Process Details:\n";
    std::cout << "PID     Arrival  Burst   Start   Finish  Turnaround  Waiting  Response\n";
    std::cout << "------- -------- ------- ------- ------- ----------- -------- ---------\n";

    for (const auto& process : processes) {
        std::cout << std::left
                << std::setw(8) << process.pid
                << std::setw(9) << process.arrival_time
                << std::setw(8) << process.burst_time
                << std::setw(8) << process.start_time
                << std::setw(8) << process.completion_time
                << std::setw(12) << process.turnaround_time
                << std::setw(9) << process.waiting_time
                << std::setw(9) << process.response_time
                << "\n";
    }
}

void Scheduler::print_gantt_chart() const {
    gantt.print();
}

const std::vector<Process>& Scheduler::get_processes() const {
    return processes;
}

const GanttChart& Scheduler::get_gantt_chart() const {
    return gantt;
}

std::string Scheduler::get_algorithm_name() const {
    return algorithm_name;
}

void Scheduler::run_process(int pid, int duration) {
    Process* process = find_process_by_pid(pid);
    if (!process) {
        std::cerr << "Error: Process " << pid << " not found\n";
        return;
    }
    
    if (duration <= 0) {
        std::cerr << "Error: Invalid duration " << duration << "\n";
        return;
    }
    
    // Set start time if this is the first time running
    if (!process->has_started) {
        process->start_time = current_time;
        process->has_started = true;
    }
    
    // Update process timing
    int actual_duration = std::min(duration, process->remaining_time);
    process->remaining_time -= actual_duration;
    process->last_run_time = current_time;
    
    // Add to Gantt chart
    gantt.add_entry(pid, current_time, current_time + actual_duration);
    
    // Update current time
    current_time += actual_duration;
    
    // Set completion time if process is done
    if (process->is_complete()) {
        process->completion_time = current_time;
        process->calculate_metrics();
    }
}

void Scheduler::add_to_gantt(int pid, int start_time, int end_time) {
    gantt.add_entry(pid, start_time, end_time);
}

bool Scheduler::all_processes_complete() const {
    for (const auto& process : processes) {
        if (!process.is_complete()) {
            return false;
        }
    }
    return true;
}

std::vector<Process*> Scheduler::get_ready_processes(int time) {
    std::vector<Process*> ready;
    for (auto& process : processes) {
        if (process.arrival_time <= time && !process.is_complete()) {
            ready.push_back(&process);
        }
    }
    return ready;
}

Process* Scheduler::find_process_by_pid(int pid) {
    for (auto& process : processes) {
        if (process.pid == pid) {
            return &process;
        }
    }
    return nullptr;
}

void Scheduler::advance_time(int new_time) {
    if (new_time > current_time) {
        // Add idle time if there's a gap
        if (current_time < new_time) {
            gantt.add_idle(current_time, new_time);
        }
        current_time = new_time;
    }
}

void Scheduler::sort_by_arrival_time() {
    std::sort(processes.begin(), processes.end(), 
              [](const Process& a, const Process& b) {
                  if (a.arrival_time != b.arrival_time) {
                      return a.arrival_time < b.arrival_time;
                  }
                  return a.pid < b.pid;  // Tie breaking
              });
}

void Scheduler::sort_by_burst_time() {
    std::sort(processes.begin(), processes.end(), 
              [](const Process& a, const Process& b) {
                  if (a.burst_time != b.burst_time) {
                      return a.burst_time < b.burst_time;
                  }
                  return a.pid < b.pid;  // Tie breaking
              });
}

void Scheduler::sort_by_priority() {
    std::sort(processes.begin(), processes.end(), 
              [](const Process& a, const Process& b) {
                  if (a.priority != b.priority) {
                      return a.priority < b.priority;  // Lower number = higher priority
                  }
                  return a.pid < b.pid;  // Tie breaking
              });
}

void Scheduler::sort_by_remaining_time() {
    std::sort(processes.begin(), processes.end(), 
              [](const Process& a, const Process& b) {
                  if (a.remaining_time != b.remaining_time) {
                      return a.remaining_time < b.remaining_time;
                  }
                  return a.pid < b.pid;  // Tie breaking
              });
}

// Forward declarations are no longer needed since we include the implementations above

Scheduler* create_scheduler(const std::string& algorithm) {
    if (algorithm == "fcfs" || algorithm == "fifo") {
        return new FCFSScheduler();
    } else if (algorithm == "sjf") {
        return new SJFScheduler();
    } else if (algorithm == "stcf" || algorithm == "srtf") {
        return new STCFScheduler();
    } else if (algorithm == "rr") {
        return new RoundRobinScheduler();
    } else {
        throw std::runtime_error("Unknown scheduling algorithm: " + algorithm);
    }
}
