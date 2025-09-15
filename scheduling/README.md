# CPU Scheduling Simulator Assignment

## Overview
This assignment will help you understand and implement various CPU scheduling algorithms. You'll work with a simulation framework that models processes and implements different scheduling strategies.

## What's Provided
- Process class and simulation framework
- Visualization tools for Gantt charts
- Performance metrics calculation framework
- Test cases and sample data
- Makefile for easy compilation

## What You Need to Implement
1. **First Come First Serve (FCFS)** - `schedulers/fcfs.cpp`
2. **Shortest Job First (SJF)** - `schedulers/sjf.cpp`
3. **Shortest Time to Completion First (STCF)** - `schedulers/stcf.cpp`
4. **Round Robin (RR)** - `schedulers/round_robin.cpp`
5. **Performance Metrics** - Complete functions in `metrics/performance.cpp`

## Compilation
```bash
make all          # Compile everything
make test         # Run test cases
make clean        # Clean build files
```

## Running the Simulator
```bash
./scheduler <algorithm> <input_file>
```

Example:
```bash
./bin/scheduler fcfs test_data/simple.txt
./bin/scheduler rr test_data/interactive.txt
```

## Project Structure
```
scheduling/
├── include/           # Header files
├── src/              # Core implementation
├── schedulers/       # Your algorithm implementations
├── metrics/          # Performance calculation
├── test_data/        # Sample process files
├── tests/            # Unit tests
└── README.md
```

## Assignment Tips
1. Start with FCFS and follow the implementation in class
2. Understand the Process class structure
3. Use the provided visualization tools to debug
4. Test with different workloads
5. Pay attention to edge cases and create some test cases by yourself

## Grading Criteria
- Correctness of algorithm implementation
- Code organization along with documentation and comments
- Performance metrics implementation

## Due Date
Before Lab-08. There will be a viva and an in-class assignment asking for an extension of the assignment.

## Academic Integrity
This is an individual assignment. You may discuss concepts, but you must implement your own code. Your final marks for the assignment depend on your ability to explain any part of the code you wrote (during the viva).
