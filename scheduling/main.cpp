#include "scheduler.h"
#include "file_parser.h"
#include "performance.h"
#include <iostream>
#include <memory>
#include <string>

void print_usage(const std::string& program_name) {
    std::cout << "CPU Scheduling Simulator\n\n";
    std::cout << "Usage: " << program_name << " <algorithm> <input_file> [options]\n\n";
    std::cout << "Algorithms:\n";
    std::cout << "  fcfs, fifo    - First Come First Serve\n";
    std::cout << "  sjf           - Shortest Job First\n";
    std::cout << "  stcf, srtf    - Shortest Time to Completion First\n";
    std::cout << "  rr            - Round Robin\n\n";
    std::cout << "Options:\n";
    std::cout << "  --no-gantt    - Don't display Gantt chart\n";
    std::cout << "  --detailed    - Show detailed performance metrics\n";
    std::cout << "  --help        - Show this help message\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << program_name << " fcfs test_data/simple.txt\n";
    std::cout << "  " << program_name << " rr test_data/interactive.txt --detailed\n";
}

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    std::string algorithm = argv[1];
    
    // Handle help and special commands
    if (algorithm == "--help" || algorithm == "-h") {
        print_usage(argv[0]);
        return 0;
    }
    
    if (algorithm == "--generate-samples") {
        std::cout << "Generating sample data files...\n";
        FileParser::generate_sample_files();
        return 0;
    }
    
    if (argc < 3) {
        std::cerr << "Error: Input file required\n";
        print_usage(argv[0]);
        return 1;
    }
    
    std::string input_file = argv[2];
    
    // Parse command line options
    bool show_gantt = true;
    bool detailed_metrics = false;
    
    for (int i = 3; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--no-gantt") {
            show_gantt = false;
        } else if (arg == "--detailed") {
            detailed_metrics = true;
        } else {
            std::cerr << "Warning: Unknown option " << arg << "\n";
        }
    }
    
    try {
        // Load processes from file
        std::cout << "Loading processes from: " << input_file << "\n";
        std::vector<Process> processes = FileParser::parse_file(input_file);
        std::cout << "Loaded " << processes.size() << " processes\n\n";
        
        // Create scheduler
        std::unique_ptr<Scheduler> scheduler(create_scheduler(algorithm));
        
        // Load processes and run simulation
        scheduler->load_processes(processes);
        scheduler->schedule();
        
        // Display results
        scheduler->print_results();
        
        if (show_gantt) {
            scheduler->print_gantt_chart();
        }
        
        // Calculate and display performance metrics
        PerformanceMetrics metrics(scheduler->get_processes(), scheduler->get_gantt_chart());
        
        if (detailed_metrics) {
            metrics.print_detailed();
        } else {
            metrics.print_summary();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
