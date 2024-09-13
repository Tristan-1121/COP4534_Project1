# Compiler and flags
CXX = g++
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./program

# Source files and object files
SRC = program/main.cpp program/cipher.cpp program/hash-table.cpp program/password-manager.cpp
OBJ = build/main.o build/cipher.o build/hash-table.o build/password-manager.o

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

# Rules to compile .cpp files into .o files
build/main.o: program/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/cipher.o: program/cipher.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/hash-table.o: program/hash-table.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/password-manager.o: program/password-manager.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f build/*.o $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the executable
run: $(TARGET)
	./$(TARGET)
