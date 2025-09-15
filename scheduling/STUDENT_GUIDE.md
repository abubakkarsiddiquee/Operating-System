# Quick Start Guide

## Getting Started

### 1. Compile the Project
```bash
make all
```

### 2. Test Basic Functionality
```bash
make test
```

### 3. Run the Working Example (FCFS)
```bash
./bin/scheduler fcfs test_data/simple.txt
```

### 4. Check All Available Options
```bash
./bin/scheduler --help
```

## Testing Strategy

### Test Each Algorithm Incrementally
```bash
# Start simple
./bin/scheduler fcfs test_data/simple.txt

# Then try your implementations
./bin/scheduler sjf test_data/simple.txt
./bin/scheduler rr test_data/interactive.txt
./bin/scheduler stcf test_data/mixed.txt
```

### Edge Case Testing
```bash
# All processes arrive at once
./bin/scheduler sjf test_data/simultaneous.txt

# Interactive workload
./bin/scheduler rr test_data/interactive.txt

# Priority-based
./bin/scheduler rr test_data/priority.txt
```

## Common Issues and Solutions

### Compilation Errors
- Make sure all TODO sections are replaced with actual implementation
- Don't leave empty function bodies
- Use the provided helper functions

### Runtime Errors
- Check for infinite loops in your scheduling logic
- Ensure you're advancing time when no process is ready
- Verify all processes get scheduled

### Incorrect Results
- Compare your output with FCFS (which is working)
- Use simple test cases first
- Add debug prints to see what your algorithm is doing

## Key Helper Functions

```cpp
// Use these in your implementations:

// Time management
advance_time(new_time)           // Jump to specific time
current_time                     // Current simulation time

// Process management  
get_ready_processes(time)        // Get arrived processes
run_process(pid, duration)       // Execute a process
all_processes_complete()         // Check if done

// Process finding/sorting
find_process_by_pid(pid)         // Find specific process
sort_by_arrival_time()           // Sort by arrival
sort_by_burst_time()             // Sort by burst time
sort_by_remaining_time()         // Sort by remaining time
```

## Expected Performance (Simple Test Case)

For `test_data/simple.txt` (processes: P1(0,5), P2(1,3), P3(2,8), P4(3,6)):

**FCFS Results:**
- Avg Turnaround: 11.25
- Avg Waiting: 5.75  
- CPU Utilization: 100%

**SJF Should Give:**
- Better average waiting time
- Same CPU utilization
- Different process order

**Round Robin Should Give:**
- Better response times
- More context switches
- Fair time sharing

Good luck with your implementation!
