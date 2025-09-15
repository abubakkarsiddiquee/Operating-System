#include "process.h"
#include <iostream>
#include <sstream>

Process::Process(int pid, int arrival, int burst, int priority, const std::string& name)
    : pid(pid), name(name), arrival_time(arrival), burst_time(burst), 
      remaining_time(burst), priority(priority), start_time(-1), 
      completion_time(-1), waiting_time(0), turnaround_time(0), 
      response_time(-1), has_started(false), last_run_time(-1) {
    
    // Set default name if not provided
    if (this->name.empty()) {
        this->name = "P" + std::to_string(pid);
    }
}

Process::Process(const Process& other)
    : pid(other.pid), name(other.name), arrival_time(other.arrival_time),
      burst_time(other.burst_time), remaining_time(other.remaining_time),
      priority(other.priority), start_time(other.start_time),
      completion_time(other.completion_time), waiting_time(other.waiting_time),
      turnaround_time(other.turnaround_time), response_time(other.response_time),
      has_started(other.has_started), last_run_time(other.last_run_time) {}

Process& Process::operator=(const Process& other) {
    if (this != &other) {
        pid = other.pid;
        name = other.name;
        arrival_time = other.arrival_time;
        burst_time = other.burst_time;
        remaining_time = other.remaining_time;
        priority = other.priority;
        start_time = other.start_time;
        completion_time = other.completion_time;
        waiting_time = other.waiting_time;
        turnaround_time = other.turnaround_time;
        response_time = other.response_time;
        has_started = other.has_started;
        last_run_time = other.last_run_time;
    }
    return *this;
}

bool Process::is_complete() const {
    return remaining_time <= 0;
}

void Process::reset_for_simulation() {
    remaining_time = burst_time;
    start_time = -1;
    completion_time = -1;
    waiting_time = 0;
    turnaround_time = 0;
    response_time = -1;
    has_started = false;
    last_run_time = -1;
}

void Process::calculate_metrics() {
    if (completion_time >= 0 && arrival_time >= 0) {
        turnaround_time = completion_time - arrival_time;
        
        if (start_time >= 0) {
            response_time = start_time - arrival_time;
            waiting_time = turnaround_time - burst_time;
        }
    }
}

std::string Process::to_string() const {
    std::ostringstream oss;
    oss << name << "(PID:" << pid << ", Arrival:" << arrival_time 
        << ", Burst:" << burst_time;
    if (priority != 0) {
        oss << ", Priority:" << priority;
    }
    oss << ")";
    return oss.str();
}

void Process::print_details() const {
    std::cout << "Process " << name << " (PID " << pid << "):\n";
    std::cout << "  Arrival Time: " << arrival_time << "\n";
    std::cout << "  Burst Time: " << burst_time << "\n";
    std::cout << "  Priority: " << priority << "\n";
    
    if (has_started) {
        std::cout << "  Start Time: " << start_time << "\n";
        std::cout << "  Completion Time: " << completion_time << "\n";
        std::cout << "  Turnaround Time: " << turnaround_time << "\n";
        std::cout << "  Waiting Time: " << waiting_time << "\n";
        std::cout << "  Response Time: " << response_time << "\n";
    } else {
        std::cout << "  Status: Not yet scheduled\n";
    }
    std::cout << "\n";
}

bool Process::operator<(const Process& other) const {
    // Default comparison by arrival time
    if (arrival_time != other.arrival_time) {
        return arrival_time < other.arrival_time;
    }
    // Tie-breaking by PID
    return pid < other.pid;
}
