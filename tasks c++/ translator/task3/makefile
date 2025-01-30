# Variables to hold the directories
SRC_DIR := src
INC_DIR := include
BIN_DIR := bin

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -I$(INC_DIR)

# Find all the cpp files in the src directory
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files are the same as sources, but with .o extension
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Default target
all: $(BIN_DIR)/program

# Rule to link the program
$(BIN_DIR)/program: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile the cpp files into object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Phony target to clean the workspace
.PHONY: clean

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/program

