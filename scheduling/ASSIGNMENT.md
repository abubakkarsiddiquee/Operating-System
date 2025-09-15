# CPU Scheduling Assignment Instructions

## Overview
You will implement four different CPU scheduling algorithms and complete performance metric calculations. This assignment will help you understand how different scheduling strategies affect system performance.

## What You Need to Do

### Part 1: Implement Scheduling Algorithms (80 points)

#### 1. First Come First Serve (FCFS) - 20 points
**File:** `schedulers/fcfs.cpp`
- **Algorithm:** Execute processes in arrival order
- **Key Points:** Non-preemptive, simple queue-based
- **Implementation:** Sort by arrival time, run each process completely

#### 2. Shortest Job First (SJF) - 20 points  
**File:** `schedulers/sjf.cpp`
- **Algorithm:** Always pick the shortest job among ready processes
- **Key Points:** Non-preemptive, optimal for average waiting time
- **Implementation:** At each decision point, find shortest burst time among ready processes

#### 3. Shortest Time to Completion First (STCF) - 20 points
**File:** `schedulers/stcf.cpp`  
- **Algorithm:** Always run process with shortest remaining time
- **Key Points:** Preemptive version of SJF
- **Implementation:** Check every time unit for better (shorter) process

#### 4. Round Robin (RR) - 20 points
**File:** `schedulers/round_robin.cpp`
- **Algorithm:** Give each process a fixed time slice in circular order
- **Key Points:** Preemptive, fair, no starvation
- **Implementation:** Use a queue, rotate processes after time quantum

### Part 2: Performance Metrics (20 points)

**File:** `metrics/performance.cpp`

Complete these functions:
- `calculate_average_turnaround_time()` - 5 points
- `calculate_average_waiting_time()` - 5 points  
- `calculate_average_response_time()` - 5 points
- `calculate_throughput()` - 5 points

## Implementation Guidelines

### Getting Started
1. Start with FCFS (simplest algorithm)
2. Test with `test_data/simple.txt`
3. Use provided helper functions in Scheduler base class
4. Move to SJF, then STCF, then RR

### Key Helper Functions Available
```cpp
// In Scheduler base class:
run_process(pid, duration)        // Execute a process
advance_time(new_time)           // Handle idle periods
get_ready_processes(time)        // Get processes that have arrived
all_processes_complete()         // Check if simulation done
find_process_by_pid(pid)         // Find process by ID
sort_by_arrival_time()          // Sort processes by arrival
sort_by_burst_time()            // Sort by burst time
sort_by_remaining_time()        // Sort by remaining time
```

### Common Patterns
```cpp
// Basic scheduling loop:
while (!all_processes_complete()) {
    auto ready = get_ready_processes(current_time);
    if (ready.empty()) {
        // Advance time to next arrival
    } else {
        // Pick process based on algorithm
        // Run the process
    }
}

// For preemptive algorithms:
run_process(pid, 1);  // Run for 1 time unit to allow preemption

// For non-preemptive:
run_process(pid, process.burst_time);  // Run to completion
```

## Testing Your Implementation

### Compilation
```bash
make all          # Compile everything
make test         # Run basic tests
make demo         # Run with sample data
```

### Running Individual Algorithms
```bash
./bin/scheduler fcfs test_data/simple.txt
./bin/scheduler sjf test_data/simple.txt  
./bin/scheduler stcf test_data/simple.txt
./bin/scheduler rr test_data/interactive.txt
```

### Test Data Files
- `simple.txt` - Basic 4-process test case
- `interactive.txt` - Good for Round Robin
- `priority.txt` - Processes with different priorities  
- `mixed.txt` - Comprehensive test case
- `simultaneous.txt` - All processes arrive at time 0

### Expected Output Example
```
=== First Come First Serve (FCFS) Scheduling Results ===

Process Details:
PID    Arrival    Burst    Start    Finish    Turnaround    Waiting    Response
---    -------    -----    -----    ------    ----------    -------    --------
1      0          5        0        5         5             0          0
2      1          3        5        8         7             4          4
...

=== Gantt Chart ===
|  P1  |P2|    P3    |  P4  |
0-----5--8----------16----22

=== Performance Metrics Summary ===
Average Turnaround Time: 12.50 time units
Average Waiting Time:    6.00 time units  
Average Response Time:   4.50 time units
CPU Utilization:         95.45%
Throughput:              0.18 processes/time unit
```

## Debugging Tips

1. **Print intermediate steps** while developing
2. **Check edge cases:** All arrive at time 0, single process, etc.
3. **Verify Gantt chart** makes sense visually
4. **Compare results** between algorithms on same input
5. **Use simple test cases** first, then complex ones

## Submission Requirements

1. **Complete all TODO sections** in the template files
2. **Test with all provided test cases**
3. **Include a brief report** (1-2 pages) comparing algorithm performance
4. **Submit via eLMS** before Lab-08.
