# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
SCHEDULER_DIR = schedulers
METRICS_DIR = metrics
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Source files
CORE_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
SCHEDULER_SOURCES = $(wildcard $(SCHEDULER_DIR)/*.cpp)
METRICS_SOURCES = $(wildcard $(METRICS_DIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
CORE_OBJECTS = $(CORE_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SCHEDULER_OBJECTS = $(SCHEDULER_SOURCES:$(SCHEDULER_DIR)/%.cpp=$(OBJ_DIR)/%.o)
METRICS_OBJECTS = $(METRICS_SOURCES:$(METRICS_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# All object files
ALL_OBJECTS = $(CORE_OBJECTS) $(SCHEDULER_OBJECTS) $(METRICS_OBJECTS)

# Executables
MAIN_EXEC = $(BIN_DIR)/scheduler
TEST_EXEC = $(BIN_DIR)/test_runner

# Default target
all: $(MAIN_EXEC)

# Main executable
$(MAIN_EXEC): $(ALL_OBJECTS) $(OBJ_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Test executable
$(TEST_EXEC): $(ALL_OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Core object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Scheduler object files
$(OBJ_DIR)/%.o: $(SCHEDULER_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Metrics object files
$(OBJ_DIR)/%.o: $(METRICS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Main object file
$(OBJ_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test target
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Run with sample data
demo: $(MAIN_EXEC)
	@echo "Running FCFS demo..."
	./$(MAIN_EXEC) fcfs test_data/simple.txt
	@echo "\nRunning Round Robin demo..."
	./$(MAIN_EXEC) rr test_data/interactive.txt

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild everything
rebuild: clean all

.PHONY: all test demo clean rebuild
