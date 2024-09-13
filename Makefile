# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./program

# Source files and object files
SRC = program/main.cpp
OBJ = build/main.o

# Output executable
TARGET = password_manager

# Default target
all: build $(TARGET)

# Create build directory
build:
	mkdir -p build

# Link the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Rule to compile .cpp files into .o files
build/main.o: program/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f build/*.o $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the executable
run: $(TARGET)
	./$(TARGET)

