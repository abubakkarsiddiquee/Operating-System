#include "gantt_chart.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void GanttChart::add_entry(int pid, int start_time, int end_time) {
    if (start_time >= end_time) {
        std::cerr << "Error: Invalid time range for Gantt entry\n";
        return;
    }
    
    entries.push_back(GanttEntry(pid, start_time, end_time));
}

void GanttChart::add_idle(int start_time, int end_time) {
    add_entry(-1, start_time, end_time);  // -1 represents idle time
}

void GanttChart::clear() {
    entries.clear();
}

void GanttChart::print() const {
    if (entries.empty()) {
        std::cout << "Empty Gantt Chart\n";
        return;
    }
    
    std::cout << "\n=== Gantt Chart ===\n";
    
    // Print process names/IDs
    std::cout << "|";
    for (const auto& entry : entries) {
        if (entry.is_idle()) {
            std::cout << std::setw(entry.duration() * 2) << "IDLE" << "|";
        } else {
            std::cout << std::setw(entry.duration() * 2) << ("P" + std::to_string(entry.pid)) << "|";
        }
    }
    std::cout << "\n";
    
    // Print time line
    std::cout << "0";
    for (const auto& entry : entries) {
        for (int i = 0; i < entry.duration() * 2 - 1; i++) {
            std::cout << "-";
        }
        std::cout << entry.end_time;
    }
    std::cout << "\n\n";
}

void GanttChart::print_detailed() const {
    if (entries.empty()) {
        std::cout << "Empty Gantt Chart\n";
        return;
    }
    
    std::cout << "\n=== Detailed Gantt Chart ===\n";
    std::cout << "Time\tProcess\tDuration\n";
    std::cout << "----\t-------\t--------\n";
    
    for (const auto& entry : entries) {
        std::cout << entry.start_time << "-" << entry.end_time << "\t";
        if (entry.is_idle()) {
            std::cout << "IDLE";
        } else {
            std::cout << "P" << entry.pid;
        }
        std::cout << "\t" << entry.duration() << "\n";
    }
    std::cout << "\n";
}

const std::vector<GanttEntry>& GanttChart::get_entries() const {
    return entries;
}

int GanttChart::get_total_time() const {
    if (entries.empty()) return 0;
    return entries.back().end_time;
}

int GanttChart::get_total_idle_time() const {
    int idle_time = 0;
    for (const auto& entry : entries) {
        if (entry.is_idle()) {
            idle_time += entry.duration();
        }
    }
    return idle_time;
}

double GanttChart::get_cpu_utilization() const {
    int total_time = get_total_time();
    if (total_time == 0) return 0.0;
    
    int active_time = total_time - get_total_idle_time();
    return (double)active_time / total_time * 100.0;
}

bool GanttChart::is_valid() const {
    if (entries.empty()) return true;
    
    // Check for gaps or overlaps
    for (size_t i = 1; i < entries.size(); i++) {
        if (entries[i-1].end_time != entries[i].start_time) {
            return false;  // Gap or overlap found
        }
    }
    
    // Check that first entry starts at 0 or later
    if (entries[0].start_time < 0) {
        return false;
    }
    
    return true;
}
