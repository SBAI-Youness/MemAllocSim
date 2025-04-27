# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Werror -Wextra -Wpedantic

# Directories
SOURCE_DIR = source
BUILD_DIR = build

# Recursive wildcard function
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Source files
SOURCES = $(call rwildcard,$(SOURCE_DIR)/,*.c)

# Target executable
TARGET = $(BUILD_DIR)/memallocsim.exe

# Default target
all: $(TARGET)

# Create build directory
$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Build target
$(TARGET): $(SOURCES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Run the program after building
run: $(TARGET)
	@$(TARGET)

# Delete the build directory
clean:
	rmdir /S /Q $(BUILD_DIR)

.PHONY: all clean run