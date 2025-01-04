# Compiler settings
#CC = gcc
#CXX = g++
CFLAGS = -Wall
LDFLAGS =

# Optional: Use clang as the compiler
# Uncomment to use clang instead of gcc
CC = clang
CXX = clang++

# Build types
DEBUG_FLAGS = -g -O0    # Debug flags
OPTIMIZED_FLAGS = -O3   # Optimized flags for production

# Files
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))
LIB_OBJ = $(filter-out main.o, $(OBJ))
EXEC = async_main
LIBRARY = lib_async_custom
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

lib: $(OBJ)
	ar rcs $(OUTPUT_DIR)/$(LIBRARY) $(LIB_OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable
$(OUTPUT_DIR)/$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)



# Ensure the output directory exists before compiling object files
$(OUTPUT_DIR):
	mkdir -p $@

# Clean up the build
clean:
	rm -f *.o $(OUTPUT_DIR)/$(EXEC)

# Remove all build artifacts (including .o files and executable)
distclean: clean
	rm -rf $(OUTPUT_DIR) Makefile

.PHONY: all debug optimized clean distclean  # Declare phony targets

