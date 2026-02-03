# Cats vs Dogs... vs Chickens - Makefile
# Build system for the RTS game

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I./include -I./lib
LDFLAGS := -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# Directories
SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

# Target executable
TARGET := $(BUILD_DIR)/rts_game

# Source files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Debug build
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: clean $(TARGET)

# Release build
release: CXXFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)

# Link executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	@echo "Clean complete"

# Run the application
run: $(TARGET)
	./$(TARGET)

# Install dependencies (Ubuntu/Debian)
install-deps:
	@echo "Installing dependencies..."
	sudo apt-get update
	sudo apt-get install -y build-essential libglfw3-dev libvulkan-dev vulkan-tools

# Print variables for debugging
print-%:
	@echo $* = $($*)

.PHONY: all debug release clean run install-deps
