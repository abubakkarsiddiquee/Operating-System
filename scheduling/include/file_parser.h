#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include "process.h"
#include <vector>
#include <string>

/**
 * Utility class for reading process data from files
 * Supports different file formats for flexibility
 */
class FileParser {
public:
    // Parse process data from file
    static std::vector<Process> parse_file(const std::string& filename);
    
    // Parse from string (useful for testing)
    static std::vector<Process> parse_string(const std::string& data);
    
    // Generate sample data files
    static void generate_sample_files();
    
private:
    // Helper functions
    static std::vector<std::string> split_line(const std::string& line, char delimiter = ' ');
    static bool is_comment_or_empty(const std::string& line);
    static Process parse_process_line(const std::string& line, int line_number);
};

#endif // FILE_PARSER_H
