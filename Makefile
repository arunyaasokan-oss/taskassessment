# --- Compiler and Flags ---
CC      := gcc
CFLAGS  := -Wall -Wextra -I./source
LDFLAGS := 

# --- Analysis Tools ---
CPPCHECK := cppcheck
# Path to the MISRA addon (standard path for many Linux distros)
# You can also create a misra.json file to map specific rules.
MISRA_ADDON := --addon=misra.json

# --- Directories ---
SRC_DIR := source
OBJ_DIR := obj

# --- Files ---
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_FILES += main.c
OBJ_FILES := $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))

# --- Output Name ---
TARGET := my_program

# --- Rules ---

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# --- Static Analysis Rules ---

# Standard Cppcheck run
check:
	$(CPPCHECK) --std=c99 --enable=all --suppress=missingIncludeSystem --suppress=variableScope  --suppress=unreadVariable $(SRC_FILES) -I./source

# MISRA C Compliance Check
# Note: This requires a 'misra.json' file in your project root
misra:
	$(CPPCHECK) $(MISRA_ADDON) --suppress=missingIncludeSystem $(SRC_FILES) -I./source

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean check misra