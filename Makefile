TARGET      := bin/main
SRC_DIR     := src
BUILD_DIR   := build
INCLUDE_DIR := include
INCLUDE_DIRS := $(shell find $(INCLUDE_DIR) -type d)

SRC_FILES   := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ_FILES   := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Compiler and Flags
CXX         := g++
CXXFLAGS    := -std=c++17 -Wall -Wextra -O2 $(addprefix -I,$(INCLUDE_DIRS))
DEBUG_FLAGS := -g

# Phony targets
.PHONY: all debug run clean clean-all

# Default build
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJ_FILES) -o $@

# Compile .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS += -DDEBUG
debug: all

# Run program
run: all
	@./$(TARGET)

# Clean build files
clean:
	@echo "Cleaning build files..."
	rm -rf $(BUILD_DIR) $(TARGET)

# Clean and run the program
a: clean run