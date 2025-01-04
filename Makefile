# Compiler settings
#CC = gcc                # Default compiler
CXX = g++                # C++ compiler (optional)
CFLAGS = -Wall           # Common flags
LDFLAGS =                # Linker flags (if any)

# Optional: Use clang as the compiler
# Uncomment to use clang instead of gcc
 CC = clang
# CXX = clang++

# Build types
DEBUG_FLAGS = -g -O0     # Debug flags
OPTIMIZED_FLAGS = -O3    # Optimized flags for production

# Files
SRC = $(wildcard *.c)     # All .c files in the current directory
OBJ = $(SRC:.c=.o)        # .o files corresponding to the .c files
EXEC = async_main         # Output executable
OUTPUT_DIR = output       # Directory to store the executable and object files

# Ensure the output directory exists
$(shell mkdir -p $(OUTPUT_DIR))

# Default target (will build with default settings)
all: $(OUTPUT_DIR)/$(EXEC)

# Debug target (to build with debug flags)
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(OUTPUT_DIR)/$(EXEC)

# Optimized target (to build with optimized flags)
optimized: CFLAGS += $(OPTIMIZED_FLAGS)
optimized: $(OUTPUT_DIR)/$(EXEC)

# Rule to build the executable
$(OUTPUT_DIR)/$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(OUTPUT_DIR)/$(EXEC) $(LDFLAGS)

# Rule to compile .c files into .o files in the output folder
$(OUTPUT_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(OUTPUT_DIR)/$@

# Clean up the build
clean:
	rm -f $(OUTPUT_DIR)/*.o $(OUTPUT_DIR)/$(EXEC)

# Remove all build artifacts (including .o files and executable)
distclean: clean
	rm -rf $(OUTPUT_DIR) Makefile
