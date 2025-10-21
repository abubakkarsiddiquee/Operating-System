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
         << setw(10) << "AT"
         << setw(10) << "BT"
         << setw(10) << "CT"
         << setw(10) << "TAT"
         << setw(10) << "WT"
         << setw(10) << "RT" << endl;
    cout << string(65, '-') << endl;

    double total_tat = 0;
    double total_wt = 0;
    double total_rt = 0;

    for (int i = 0; i < n; i++) {
        total_tat += p[i].turn_around_time;
        total_wt += p[i].waiting_time;
        total_rt += p[i].response_time;

        cout << left << setw(15) << p[i].process_name
             << setw(10) << p[i].arrival_time
             << setw(10) << p[i].burst_time
             << setw(10) << p[i].completion_time
             << setw(10) << p[i].turn_around_time
             << setw(10) << p[i].waiting_time
             << setw(10) << p[i].response_time << endl;
    }

    cout << string(65, '-') << endl;
    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time: " << (total_tat / n) << endl;
    cout << "Average Waiting Time:    " << (total_wt / n) << endl;
    cout << "Average Response Time:   " << (total_rt / n) << endl;
}

// Main scheduling logic (Round Robin)
void Calculate_CT(Process p[], int n, int time_quantum) {
    vector<Process> processes(p, p + n); // Use vector for dynamic queue/copy
    queue<int> ready_queue;
    vector<GanttEntry> gantt_chart;
    
    int current_time = 0;
    int completed_processes = 0;
    int process_index = 0; // Index for initial arrival sort

    // Initial sort by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    // Tracking if a process has entered the queue for the first time
    vector<bool> in_queue(n, false);
    
    // Add the first process that arrives earliest
    if (n > 0) {
        ready_queue.push(0); 
        in_queue[0] = true;
    }

    while (completed_processes < n) {
        if (ready_queue.empty()) {
            // CPU is IDLE
            int next_arrival = INT_MAX;
            int next_index = -1;
            
            for(int i = 0; i < n; ++i) {
                if (!in_queue[i] && processes[i].arrival_time < next_arrival) {
                    next_arrival = processes[i].arrival_time;
                    next_index = i;
                }
            }

            if (next_index != -1) {
                // Handle IDLE entry
                if (gantt_chart.empty() || gantt_chart.back().process_name != "IDLE") {
                    gantt_chart.push_back({current_time, next_arrival, "IDLE"});
                } else {
                    gantt_chart.back().end_time = next_arrival;
                }
                current_time = next_arrival;
                ready_queue.push(next_index);
                in_queue[next_index] = true;
            } else {
                // Should not happen if total burst time is calculated correctly, but prevents infinite loop
                current_time++; 
            }
            continue;
        }

        int current_idx = ready_queue.front();
        ready_queue.pop();
        Process& current_p = processes[current_idx];

        // Calculate Response Time (RT) on first execution
        if (current_p.response_time == -1) {
            current_p.response_time = current_time - current_p.arrival_time;
        }

        int execution_time = min(time_quantum, current_p.remaining_time);
        int start_time = current_time;
        current_time += execution_time;
        current_p.remaining_time -= execution_time;

        // Record Gantt entry
        gantt_chart.push_back({start_time, current_time, current_p.process_name});

        // Add any newly arrived processes during this time slice
        for (int i = 0; i < n; ++i) {
            if (!in_queue[i] && processes[i].arrival_time <= current_time) {
                // Simple FCFS for RR ready queue: push to the back
                ready_queue.push(i);
                in_queue[i] = true;
            }
        }
        
        // If process is not finished, put it back in the queue
        if (current_p.remaining_time > 0) {
            ready_queue.push(current_idx);
        } else {
            // Process completed
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
        cout << "Enter process name (P" << i+1 << "), arrival time (AT) & Burst time (BT): ";
        p[i].process_name = "P" + to_string(i+1); 
        cin >> p[i].arrival_time >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
    }
    
    int time_quantum;
    cout << "Enter Time Quantum: ";
    cin >> time_quantum;

    Calculate_CT(p, n, time_quantum);
    Calculate_TAT(p, n);
    Calculate_WT(p, n);

    display(p, n);
    return 0;
}
