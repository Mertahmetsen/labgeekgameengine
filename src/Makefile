# Default library type: 'dynamic' or 'static'
BUILD_TYPE ?= dynamic

# Toolchain & Flags
CC      := gcc
CFLAGS  := -I. -O3 -Wall -Wextra -Wpedantic -fsanitize=address -g
LDFLAGS := -lraylib -lm -fsanitize=address

# Locate sources, excluding main.c
LIB_SRCS := $(filter-out ./main.c, $(shell find . -maxdepth 2 -type f -name "*.c"))
LIB_OBJS := $(LIB_SRCS:.c=.o)

BIN := ./bin

# Conditional configuration based on BUILD_TYPE
ifeq ($(BUILD_TYPE), static)
    LIB := ./liblgge.a
    # Link explicitly via file path to guarantee static linking
    LINK_LIB = $(LIB)
else
    LIB := ./liblgge.so
    CFLAGS  += -fPIC
    LDFLAGS += -L. -llgge -Wl,-rpath,'$$ORIGIN/.'
    LINK_LIB = -L. -llgge
endif

.PHONY: all clean

all: $(BIN)

# 1. Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 2. Package or link object files into the selected library type
$(LIB): $(LIB_OBJS)
ifeq ($(BUILD_TYPE), static)
	ar rcs $@ $^
else
	$(CC) -shared -o $@ $^
endif

# 3. Build executable linked against the library
$(BIN): main.c $(LIB)
	$(CC) $(CFLAGS) main.c -o $@ $(LINK_LIB) $(LDFLAGS)

# Helper rule to wipe build artifacts
clean:
	rm -f liblgge.so liblgge.a $(BIN) $(LIB_OBJS)
