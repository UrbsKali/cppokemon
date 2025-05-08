# Compiler and flags
CXX = g++
CXXFLAGS = -std=gnu++23 -Wall -Wextra -g

# Directories
SRC_DIR = src
LIB_DIR = libs/pokemon/src
INCLUDE_DIR = includes libs/pokemon/includes
DATA_DIR = data
BUILD_DIR = build
OUT_DIR = out

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
LIB_FILES = $(wildcard $(LIB_DIR)/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES)) \
			$(patsubst $(LIB_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(LIB_FILES))

# Output binary
TARGET = $(OUT_DIR)/cppokemon

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCLUDE_DIR)) -c $< -o $@

# Compile library files
$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCLUDE_DIR)) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run