# ===== Compiler =====
CC := gcc

# ===== Output =====
TARGET := build/main
OBJ_DIR := build/objects

# ===== Flags =====
CFLAGS := -Wall -Wextra -O2 -I./src
LDFLAGS := -lSDL2 -lSDL2_gfx -lm

# ===== Sources =====
SRC := $(shell find src -name "*.c")

# تبدیل src/xxx.c → build/objects/src/xxx.o
OBJ := $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))

# ===== Default =====
all: $(TARGET) run

# ===== Link =====
$(TARGET): $(OBJ) | build
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# ===== Compile =====
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ===== Create dirs =====
build:
	mkdir -p build $(OBJ_DIR)

# ===== Run =====
run: $(TARGET)
	./$(TARGET)

# ===== Clean =====
clean:
	rm -rf build

# ===== Rebuild =====
re: clean all

.PHONY: all clean re build run
