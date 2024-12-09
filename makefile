# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Targets
TARGET = RiverTree
TEST_TARGET = TestRiverTree

# Source files and object files (for .c++ extension)
SRC = main.c++ river_binary_tree.c++
TEST_SRC = test.c++ river_binary_tree.c++

# Generate object files for each source file
OBJ = $(SRC:.c++=.o)
TEST_OBJ = $(TEST_SRC:.c++=.o)

# Default target
all: $(TARGET) $(TEST_TARGET)

# Rule to build the main program
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Rule to build the test executable
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJ)

# Pattern rule for building object files (for .c++ source files)
%.o: %.c++
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

# Run the main program
run: $(TARGET)
	./$(TARGET)

# Run the tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Prevent make from treating these names as files
.PHONY: all clean run test