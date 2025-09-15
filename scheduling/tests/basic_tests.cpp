#include "process.h"
#include "file_parser.h"
#include "gantt_chart.h"
#include <iostream>
#include <cassert>

// Simple test framework
int tests_passed = 0;
int tests_failed = 0;

void assert_equal(int expected, int actual, const std::string& test_name) {
    if (expected == actual) {
        std::cout << "✓ " << test_name << " PASSED\n";
        tests_passed++;
    } else {
        std::cout << "✗ " << test_name << " FAILED: expected " << expected 
                  << ", got " << actual << "\n";
        tests_failed++;
    }
}

void assert_equal(double expected, double actual, const std::string& test_name) {
    if (abs(expected - actual) < 0.001) {
        std::cout << "✓ " << test_name << " PASSED\n";
        tests_passed++;
    } else {
        std::cout << "✗ " << test_name << " FAILED: expected " << expected 
                  << ", got " << actual << "\n";
        tests_failed++;
    }
}

void assert_equal(const std::string& expected, const std::string& actual, const std::string& test_name) {
    if (expected == actual) {
        std::cout << "✓ " << test_name << " PASSED\n";
        tests_passed++;
    } else {
        std::cout << "✗ " << test_name << " FAILED: expected '" << expected 
                  << "', got '" << actual << "'\n";
        tests_failed++;
    }
}

void test_process_creation() {
    std::cout << "\n=== Testing Process Creation ===\n";
    
    Process p1(1, 0, 5);
    assert_equal(1, p1.pid, "Process PID");
    assert_equal(0, p1.arrival_time, "Process arrival time");
    assert_equal(5, p1.burst_time, "Process burst time");
    assert_equal(5, p1.remaining_time, "Process remaining time");
    
    Process p2(2, 3, 7, 1, "TestProcess");
    assert_equal(2, p2.pid, "Named process PID");
    assert_equal("TestProcess", p2.name, "Process name");
    assert_equal(1, p2.priority, "Process priority");
}

void test_process_metrics() {
    std::cout << "\n=== Testing Process Metrics ===\n";
    
    Process p(1, 0, 5);
    p.start_time = 2;
    p.completion_time = 7;
    p.calculate_metrics();
    
    assert_equal(7, p.turnaround_time, "Turnaround time calculation");
    assert_equal(2, p.waiting_time, "Waiting time calculation");
    assert_equal(2, p.response_time, "Response time calculation");
}

void test_file_parser() {
    std::cout << "\n=== Testing File Parser ===\n";
    
    std::string test_data = "1 0 5\n2 1 3 2 TestProc\n# Comment line\n\n3 4 7";
    std::vector<Process> processes = FileParser::parse_string(test_data);
    
    assert_equal(3, (int)processes.size(), "Number of parsed processes");
    assert_equal(1, processes[0].pid, "First process PID");
    assert_equal(0, processes[0].arrival_time, "First process arrival");
    assert_equal(5, processes[0].burst_time, "First process burst");
    
    assert_equal(2, processes[1].priority, "Second process priority");
    assert_equal("TestProc", processes[1].name, "Second process name");
}

void test_gantt_chart() {
    std::cout << "\n=== Testing Gantt Chart ===\n";
    
    GanttChart gantt;
    gantt.add_entry(1, 0, 3);
    gantt.add_entry(2, 3, 7);
    gantt.add_idle(7, 8);
    gantt.add_entry(3, 8, 10);
    
    assert_equal(10, gantt.get_total_time(), "Total time");
    assert_equal(1, gantt.get_total_idle_time(), "Idle time");
    assert_equal(90.0, gantt.get_cpu_utilization(), "CPU utilization");
    
    const auto& entries = gantt.get_entries();
    assert_equal(4, (int)entries.size(), "Number of Gantt entries");
    assert_equal(1, entries[0].pid, "First entry PID");
    assert_equal(true, entries[2].is_idle(), "Third entry is idle");
}

int main() {
    std::cout << "Running CPU Scheduler Tests...\n";
    
    test_process_creation();
    test_process_metrics();
    test_file_parser();
    test_gantt_chart();
    
    std::cout << "\n=== Test Results ===\n";
    std::cout << "Tests passed: " << tests_passed << "\n";
    std::cout << "Tests failed: " << tests_failed << "\n";
    
    if (tests_failed == 0) {
        std::cout << "🎉 All tests passed!\n";
        return 0;
    } else {
        std::cout << "❌ Some tests failed. Please check implementation.\n";
        return 1;
    }
}
