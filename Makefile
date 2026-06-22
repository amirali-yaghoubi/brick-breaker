# =====================
# Compiler
# =====================
CC := gcc

# =====================
# Output
# =====================
TARGET := build/game
OBJ_DIR := build/obj

# =====================
# Flags
# =====================
CFLAGS := -Wall -Wextra -I./src -O2
LDFLAGS := -lSDL2 -lSDL2_ttf -lSDL2_gfx -lm

# =====================
# Sources
# =====================
SRC := $(shell find src -name "*.c")
OBJ := $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))

# =====================
# Default
# =====================
all: $(TARGET)

# =====================
# Link
# =====================
$(TARGET): $(OBJ) | build
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# =====================
# Compile
# =====================
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# =====================
# Create dirs
# =====================
build:
	@mkdir -p build $(OBJ_DIR)

# =====================
# Run
# =====================
run: $(TARGET)
	./$(TARGET)

# =====================
# Debug build
# =====================
debug:
	$(MAKE) CFLAGS="-Wall -Wextra -I./src -g -O0" LDFLAGS="$(LDFLAGS)"

# =====================
# Clean
# =====================
clean:
	rm -rf build

# =====================
# Rebuild
# =====================
re: clean all

.PHONY: all clean re run debug build
