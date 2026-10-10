CC = clang

CLANG_BUILTIN = /usr/lib/llvm/21/lib/clang/21/include

CFLAGS = \
-nostdinc \
-Iinclude \
-Ithird_party \
-isystem $(CLANG_BUILTIN) \
-nostdlib \
-ffreestanding \
-fno-builtin \
-fno-stack-protector

RYU_CFLAGS = \
$(CFLAGS) \
-Icompability/glibc

LDFLAGS = \
-nostdlib \
-Wl,-no-dynamic-linker,-e,_start

START = src/one.c
MAIN = ulibc.c

SRC_SRCS = $(filter-out $(START),$(shell find src -name '*.c'))
RYU_SRCS = $(shell find third_party/ryu -name '*.c')

SRCS = $(START) $(SRC_SRCS) $(RYU_SRCS) $(MAIN)

TARGET = hello

OBJDIR = build/obj

OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/third_party/ryu/%.o: third_party/ryu/%.c
	mkdir -p $(dir $@)
	$(CC) $(RYU_CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
