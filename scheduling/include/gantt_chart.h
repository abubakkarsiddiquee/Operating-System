#ifndef GANTT_CHART_H
#define GANTT_CHART_H

#include <vector>
#include <string>

/**
 * Represents a single time slot in the Gantt chart
 */
struct GanttEntry {
    int pid;           // Process ID (-1 for idle time)
    int start_time;    // Start time of this slot
    int end_time;      // End time of this slot
    
    GanttEntry(int p, int start, int end) : pid(p), start_time(start), end_time(end) {}
    
    int duration() const { return end_time - start_time; }
    bool is_idle() const { return pid == -1; }
};

/**
 * Gantt Chart for visualizing CPU scheduling
 * Shows which process runs at what time
 */
class GanttChart {
private:
    std::vector<GanttEntry> entries;
    
public:
    // Add a time slot to the chart
    void add_entry(int pid, int start_time, int end_time);
    
    // Add idle time
    void add_idle(int start_time, int end_time);
    
    // Clear all entries
    void clear();
    
    // Display functions
    void print() const;
    void print_detailed() const;
    
    // Getters
    const std::vector<GanttEntry>& get_entries() const;
    int get_total_time() const;
    int get_total_idle_time() const;
    double get_cpu_utilization() const;
    
    // Validation
    bool is_valid() const;  // Check for gaps or overlaps
};

#endif // GANTT_CHART_H
