#include<bits/stdc++.h>
using namespace std;

// Structure to record entries for the Gantt Chart
struct GanttEntry {
    int start_time;
    int end_time;
    string process_name;
};

// Defining the structure of a process
struct Process {
    string process_name;
    int arrival_time;
    int burst_time;
    int priority; // Lower number means higher priority
    int remaining_time; 
    int completion_time = 0;
    int turn_around_time = 0;
    int waiting_time = 0;
    int response_time = -1; // Time of first execution - Arrival Time
};

// Function to calculate Turn Around Time
void Calculate_TAT(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
    }
}

// Function to calculate Waiting Time
void Calculate_WT(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
    }
}

// Function to display the Gantt Chart (adapted for preemption)
void display_gantt(const vector<GanttEntry>& gantt_chart) {
    if (gantt_chart.empty()) return;

    cout << "\n--- Gantt Chart ---\n";

    // 1. Top border and content
    for (const auto& entry : gantt_chart) {
        cout << "+---";
        for (size_t i = 0; i < entry.process_name.length(); ++i) cout << "-";
    }
    cout << "+" << endl;

    // 2. Process IDs
    for (const auto& entry : gantt_chart) {
        cout << "| " << entry.process_name << " ";
    }
    cout << "|" << endl;

    // 3. Bottom border and content
    for (const auto& entry : gantt_chart) {
        cout << "+---";
        for (size_t i = 0; i < entry.process_name.length(); ++i) cout << "-";
    }
    cout << "+" << endl;

    // 4. Time stamps
    cout << setw(3) << gantt_chart[0].start_time;
    for (const auto& entry : gantt_chart) {
        cout << setw(entry.process_name.length() + 4) << entry.end_time;
    }
    cout << endl;
}

// Function to display the final metrics table
void display(Process p[], int n) {
    cout << "\n--- Results ---\n";
    cout << left << setw(15) << "Process"
         << setw(5) << "Pri"
         << setw(10) << "AT"
         << setw(10) << "BT"
         << setw(10) << "CT"
         << setw(10) << "TAT"
         << setw(10) << "WT"
         << setw(10) << "RT" << endl;
    cout << string(70, '-') << endl;

    double total_tat = 0;
    double total_wt = 0;
    double total_rt = 0;

    for (int i = 0; i < n; i++) {
        total_tat += p[i].turn_around_time;
        total_wt += p[i].waiting_time;
        total_rt += p[i].response_time;

        cout << left << setw(15) << p[i].process_name
             << setw(5) << p[i].priority
             << setw(10) << p[i].arrival_time
             << setw(10) << p[i].burst_time
             << setw(10) << p[i].completion_time
             << setw(10) << p[i].turn_around_time
             << setw(10) << p[i].waiting_time
             << setw(10) << p[i].response_time << endl;
    }

    cout << string(70, '-') << endl;
    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time: " << (total_tat / n) << endl;
    cout << "Average Waiting Time:    " << (total_wt / n) << endl;
    cout << "Average Response Time:   " << (total_rt / n) << endl;
}

// Main scheduling logic (Preemptive Priority)
void Calculate_CT(Process p[], int n) {
    vector<Process> processes(p, p + n);
    vector<GanttEntry> gantt_chart;
    
    int completed_processes = 0;
    int current_time = 0;
    
    // Calculate total timeline length
    int max_arrival = 0;
    for (const auto& proc : processes) {
        max_arrival = max(max_arrival, proc.arrival_time);
    }
    int total_burst_time = accumulate(processes.begin(), processes.end(), 0, 
        [](int sum, const Process& proc) { return sum + proc.burst_time; });
    int total_timeline_length = max(max_arrival, 0) + total_burst_time;


    while (completed_processes < n && current_time < total_timeline_length + 1) {
        int highest_priority = INT_MAX;
        int selected_process_index = -1;

        // Find the process in the ready queue with the highest priority (lowest number)
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    selected_process_index = i;
                }
                // Tie-breaker: If priorities are equal, use FCFS (earlier arrival)
                else if (processes[i].priority == highest_priority && selected_process_index != -1) {
                    if (processes[i].arrival_time < processes[selected_process_index].arrival_time) {
                         selected_process_index = i;
                    }
                }
            }
        }

        if (selected_process_index == -1) {
            // CPU is IDLE: Advance time to the next arrival
            int next_arrival = INT_MAX;
            bool found_next = false;
            for(const auto& proc : processes) {
                if(proc.remaining_time > 0) {
                    next_arrival = min(next_arrival, proc.arrival_time);
                    found_next = true;
                }
            }
            if (found_next && next_arrival != INT_MAX) {
                if (gantt_chart.empty() || gantt_chart.back().process_name != "IDLE") {
                    gantt_chart.push_back({current_time, next_arrival, "IDLE"});
                } else {
                    gantt_chart.back().end_time = next_arrival;
                }
                current_time = next_arrival;
            } else {
                current_time++;
            }
            continue; 
        }

        Process& current_p = processes[selected_process_index];

        // Calculate Response Time (RT) on first execution
        if (current_p.response_time == -1) {
            current_p.response_time = current_time - current_p.arrival_time;
        }

        // Execute for 1 unit of time
        current_p.remaining_time--;
        int start_time = current_time;
        current_time++;

        // Update Gantt Chart: Merge with previous entry if it was the same process
        if (!gantt_chart.empty() && gantt_chart.back().process_name == current_p.process_name) {
            gantt_chart.back().end_time = current_time;
        } else {
            gantt_chart.push_back({start_time, current_time, current_p.process_name});
        }

        // Check for completion
        if (current_p.remaining_time == 0) {
            current_p.completion_time = current_time;
            completed_processes++;
        }
    }

    // Copy results back to original array and sort by name for display
    for(int i = 0; i < n; ++i) { p[i] = processes[i]; }
    sort(p, p + n, [](const Process& a, const Process& b) { return a.process_name < b.process_name; });

    display_gantt(gantt_chart);
}

int main()
{
    cout << "Enter the total number of process: ";
    int n;
    cin >> n;

    Process p[n];
    for(int i = 0; i < n; i++) {
        cout << "Enter process name (P" << i+1 << "), arrival time (AT), Burst time (BT) & Priority: ";
        p[i].process_name = "P" + to_string(i+1);
        cin >> p[i].arrival_time >> p[i].burst_time >> p[i].priority;
        p[i].remaining_time = p[i].burst_time;
    }

    Calculate_CT(p, n);
    Calculate_TAT(p, n);
    Calculate_WT(p, n);

    display(p, n);
    return 0;
}
