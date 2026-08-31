BUILD_TYPE ?= dynamic
CC      := gcc
CFLAGS  := -I. -O3 -Wall -Wextra -Wpedantic -fsanitize=address -g
LDFLAGS := -L. -llgge -lraylib -lm -fsanitize=address
LIB_SRCS := $(filter-out ./main.c, $(shell find . -maxdepth 2 -type f -name "*.c"))
LIB_OBJS := $(LIB_SRCS:.c=.o)
ifeq ($(BUILD_TYPE), static)
    LIB := ./liblgge.a
    LIB_CMD = ar rcs $@ $^
else
    LIB := ./liblgge.so
    CFLAGS  += -fPIC
    LDFLAGS += -Wl,-rpath,'$$ORIGIN/.'
    LIB_CMD = $(CC) -shared -o $@ $^
endif
BIN := ./bin
.PHONY: all clean
all: $(BIN)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
$(LIB): $(LIB_OBJS)
	$(LIB_CMD)
	rm -f $(LIB_OBJS)
$(BIN): main.c $(LIB)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
clean:
	rm -f liblgge.so liblgge.a $(BIN) $(LIB_OBJS)
