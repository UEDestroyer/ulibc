CC = gcc

CFLAGS = \
	-Iinclude \
	-nostdlib \
	-ffreestanding \
	-fno-builtin \
	-fno-stack-protector

LDFLAGS = \
	-nostdlib \
	-Wl,-no-dynamic-linker,-e,_start

START = ./src/one.c

SRCS = $(filter-out ./src/one.c,$(shell find . -name '*.c'))

TARGET = hello

all: $(TARGET)

$(TARGET): $(START) $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(START) $(SRCS) -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean