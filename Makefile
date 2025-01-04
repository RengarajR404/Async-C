# Compiler settings
CC = gcc                # Default compiler
CXX = g++               # C++ compiler (optional)
CFLAGS = -Wall          # Common flags
LDFLAGS =               # Linker flags (if any)

# Optional: Use clang as the compiler
# Uncomment to use clang instead of gcc
# CC = clang
# CXX = clang++

# Build types
DEBUG_FLAGS = -g -O0    # Debug flags
OPTIMIZED_FLAGS = -O3   # Optimized flags for production

# Files
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,$(OUTPUT_DIR)/%.o,$(SRC))
EXEC = async_main
OUTPUT_DIR = output

# Ensure the output directory exists before compilation
$(shell mkdir -p $(OUTPUT_DIR))

# Default target (will build with default settings)
all: $(OUTPUT_DIR)/$(EXEC)

# Debug target (to build with debug flags)
debug: CFLAGS += $(DEBUG_FLAGS)
debug: all

# Optimized target (to build with optimized flags)
optimized: CFLAGS += $(OPTIMIZED_FLAGS)
optimized: all

# Rule to build the executable
$(OUTPUT_DIR)/$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Rule to compile .c files into .o files in the output folder
$(OUTPUT_DIR)/%.o: %.c | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the output directory exists before compiling object files
$(OUTPUT_DIR):
	mkdir -p $@

# Clean up the build
clean:
	rm -f $(OUTPUT_DIR)/*.o $(OUTPUT_DIR)/$(EXEC)

# Remove all build artifacts (including .o files and executable)
distclean: clean
	rm -rf $(OUTPUT_DIR) Makefile

.PHONY: all debug optimized clean distclean  # Declare phony targets

