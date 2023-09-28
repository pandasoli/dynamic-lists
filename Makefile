INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin
TEST_DIR = tests

LIB_NAME = dynamic-lists
LIB = $(LIB_DIR)/lib$(LIB_NAME).a
SRCS := $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TESTS := $(wildcard $(TEST_DIR)/*.c)

CC = clang
CFLAGS = -g -O3 -Wall -I$(INC_DIR)

# targets

.PHONY: all tests clean

all: $(LIB) tests

tests: $(TESTS:$(TEST_DIR)/%.c=$(BIN_DIR)/$(TEST_DIR)/%)

clean:
	rm -r $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR)

# files

$(LIB): $(OBJS)
	mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/$(TEST_DIR)/%: $(TEST_DIR)/%.c | $(LIB)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LIB_NAME)
