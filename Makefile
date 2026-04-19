# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build

# Files
TARGET = a.out

SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/Trie.cpp
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/Trie.o

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)