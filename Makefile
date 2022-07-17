CC := gcc
CFLAGS := -std=c11 -pedantic -Wall -Wextra -g

TARGET_EXEC := cpu_usage_tracker

BUILD_DIR := ./build
SRC_DIR := ./src

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# test variables ################
TEST_TARGET_EXEC := tester_cpu_usage_tracker

TEST_BUILD_DIR := ./test_build
TEST_DIR := ./tests

TEST_SRCS := $(shell find $(TEST_DIR) -name '*.c')
TEST_OBJS := $(TEST_SRCS:%=$(TEST_BUILD_DIR)/%.o)
#################################

.PHONY: all
all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ -lpthread

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test
test: $(TEST_BUILD_DIR)/$(TEST_TARGET_EXEC)

$(TEST_BUILD_DIR)/$(TEST_TARGET_EXEC): $(TEST_OBJS) $(OBJS)
	$(CC) $(TEST_OBJS) $(filter-out %/main.c.o, $(OBJS)) -o $@ -lpthread

$(TEST_BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f -r $(BUILD_DIR)
	rm -f -r $(TEST_BUILD_DIR)