#include "file_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::vector<Process> FileParser::parse_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::vector<Process> processes;
    std::string line;
    int line_number = 0;
    
    while (std::getline(file, line)) {
        line_number++;
        
        if (is_comment_or_empty(line)) {
            continue;
        }
        
        try {
            Process process = parse_process_line(line, line_number);
            processes.push_back(process);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line " << line_number << ": " << e.what() << "\n";
            std::cerr << "Line content: " << line << "\n";
        }
    }
    
    file.close();
    
    if (processes.empty()) {
        throw std::runtime_error("No valid processes found in file: " + filename);
    }
    
    return processes;
}

std::vector<Process> FileParser::parse_string(const std::string& data) {
    std::vector<Process> processes;
    std::istringstream stream(data);
    std::string line;
    int line_number = 0;
    
    while (std::getline(stream, line)) {
        line_number++;
        
        if (is_comment_or_empty(line)) {
            continue;
        }
        
        try {
            Process process = parse_process_line(line, line_number);
            processes.push_back(process);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line " << line_number << ": " << e.what() << "\n";
        }
    }
    
    return processes;
}

void FileParser::generate_sample_files() {
    // Create test_data directory if it doesn't exist
    std::ofstream simple("test_data/simple.txt");
    simple << "# Simple test case for FCFS\n";
    simple << "# Format: PID Arrival_Time Burst_Time [Priority] [Name]\n";
    simple << "1 0 5\n";
    simple << "2 1 3\n";
    simple << "3 2 8\n";
    simple << "4 3 6\n";
    simple.close();
    
    std::ofstream interactive("test_data/interactive.txt");
    interactive << "# Interactive workload - good for Round Robin\n";
    interactive << "1 0 4 0 WebBrowser\n";
    interactive << "2 1 2 0 TextEditor\n";
    interactive << "3 2 6 0 Compiler\n";
    interactive << "4 3 3 0 Calculator\n";
    interactive << "5 4 1 0 NotePad\n";
    interactive.close();
    
    std::ofstream priority("test_data/priority.txt");
    priority << "# Priority-based test case\n";
    priority << "# Lower priority number = higher priority\n";
    priority << "1 0 10 3 LowPriorityTask\n";
    priority << "2 1 4 1 HighPriorityTask\n";
    priority << "3 2 6 2 MediumPriorityTask\n";
    priority << "4 3 2 1 AnotherHighPriority\n";
    priority.close();
    
    std::ofstream mixed("test_data/mixed.txt");
    mixed << "# Mixed workload for comprehensive testing\n";
    mixed << "1 0 7 2\n";
    mixed << "2 2 4 1\n";
    mixed << "3 4 1 3\n";
    mixed << "4 5 3 1\n";
    mixed << "5 8 2 2\n";
    mixed.close();
    
    std::cout << "Sample data files generated in test_data/ directory\n";
}

std::vector<std::string> FileParser::split_line(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        // Remove leading/trailing whitespace
        size_t start = token.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        
        size_t end = token.find_last_not_of(" \t");
        token = token.substr(start, end - start + 1);
        
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

bool FileParser::is_comment_or_empty(const std::string& line) {
    // Check if line is empty or starts with #
    std::string trimmed = line;
    size_t start = trimmed.find_first_not_of(" \t");
    
    if (start == std::string::npos) return true;  // Empty line
    if (trimmed[start] == '#') return true;       // Comment line
    
    return false;
}

Process FileParser::parse_process_line(const std::string& line, int line_number) {
    std::vector<std::string> tokens = split_line(line, ' ');
    
    if (tokens.size() < 3) {
        throw std::runtime_error("Insufficient data - need at least PID, arrival time, and burst time");
    }
    
    try {
        int pid = std::stoi(tokens[0]);
        int arrival_time = std::stoi(tokens[1]);
        int burst_time = std::stoi(tokens[2]);
        
        // Validate basic constraints
        if (pid < 0) throw std::runtime_error("PID cannot be negative");
        if (arrival_time < 0) throw std::runtime_error("Arrival time cannot be negative");
        if (burst_time <= 0) throw std::runtime_error("Burst time must be positive");
        
        // Optional priority (default = 0)
        int priority = 0;
        if (tokens.size() >= 4) {
            priority = std::stoi(tokens[3]);
        }
        
        // Optional name (default = "P" + pid)
        std::string name = "";
        if (tokens.size() >= 5) {
            name = tokens[4];
        }
        
        return Process(pid, arrival_time, burst_time, priority, name);
        
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid number format in process data");
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Number out of range in process data");
    }
}
