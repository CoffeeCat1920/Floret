# Define the compiler
CXX = g++

# Define directories
SRCDIR = src
INCDIR = include
COREINCDIR = $(INCDIR)/core
RAYLIBINCDIR = $(INCDIR)/raylib
WORLDINCDIR = $(INCDIR)/world
BINDIR = bin
LIBDIR = lib

# Target executable
TARGET = $(BINDIR)/core

# Find all .cpp files in src/ and subdirectories
SRCFILES = $(wildcard $(SRCDIR)/**/*.cpp) $(wildcard $(SRCDIR)/*.cpp)

# Add main.cpp from root
SRCFILES += main.cpp

# Create corresponding .o file paths under bin/
OBJECTS = $(patsubst %.cpp, $(BINDIR)/%.o, $(SRCFILES))

# Compiler flags
CXXFLAGS = -I$(COREINCDIR) -I$(RAYLIBINCDIR) -I$(WORLDINCDIR) -std=c++17

# Linker flags
LDFLAGS = -L$(LIBDIR) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Default rule
all: $(TARGET)

# Link object files into final binary
$(TARGET): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $^ -o $@ $(LDFLAGS)

# Rule to compile .cpp files into .o files in bin/
$(BINDIR)/%.o: %.cpp
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build..."
	@rm -rf $(BINDIR)/*.o $(TARGET) $(BINDIR)/**/*.o

# Debug info
debug:
	@echo "Source files:"
	@echo $(SRCFILES)
	@echo
	@echo "Object files:"
	@echo $(OBJECTS)
	@echo
	@echo "Target: $(TARGET)"

# Run the program
run: all
	@./$(TARGET)

# Clean, build, and run
run-clean: clean all
	@./$(TARGET)

.PHONY: all clean debug run run-clean
