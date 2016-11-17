#
# '-g' option in 'CFLAGS' is for debug
# Careful, if don't use flag '-m32', (void *) has 8 bytes
#
PROJECT := dsa

##############################
# Set directories
##############################

# All of the directories containing header.
INC_DIRS := $(shell find * -type d -exec bash -c "find {} -maxdepth 1 \
	\( -name '*.h' -o -name '*.proto' \) | grep -q ." \; -print)
# INC_DIRS := include/dsa/tree
# Directories containing code.
BASIC_SRC := src/dsa/basic
TREE_SRC := src/dsa/tree
GRAPH_SRC := src/dsa/graph
TEST_SRC := src/dsa/test
SRC_DIRS := BASIC_SRC
SRC_DIRS += TREE_SRC
SRC_DIRS += GRAPH_SRC
SRC_DIRS += TEST_SRC
# Direcotry to put build files
BUILD_DIR := build

##############################
# Define build targets
##############################

TREE_OBJS := $(TREE_SRC)/tree_algo.o $(BASIC_SRC)/stack.o $(BASIC_SRC)/queue.o \
	$(TREE_SRC)/bst.o $(TREE_SRC)/tbt.o

GRAPH_OBJS := $(GRAPH_SRC)/graph_algo.o $(BASIC_SRC)/stack.o $(BASIC_SRC)/queue.o \
	$(GRAPH_SRC)/graph_adj.o 

# Tests targets
TEST_GRAPH_ADJ_OBJS := $(TEST_SRC)/test_graph_adj.o $(BASIC_SRC)/queue.o \
	$(GRAPH_SRC)/graph_adj.o

TEST_GRAPH_ALGO_OBJS := $(TEST_SRC)/test_graph_algo.o $(BASIC_SRC)/queue.o \
	$(GRAPH_SRC)/graph_adj.o $(GRAPH_SRC)/graph_algo.o

##############################
# Build
##############################
.PHONY: all

CC := gcc
CFLAGS := -Wall $(foreach INC_DIR, $(INC_DIRS), -I$(INC_DIR))

all: dir tree_algo 

dir:
# Create build directory if doesn't exist
ifneq ($(wildcard $(BUILD_DIR)),)
	@ echo "build directory already exists"
else
	@ mkdir -p $(BUILD_DIR)
endif

tree_algo: $(TREE_OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/tree_algo $(TREE_OBJS)

# graph_algo: $(GRAPH_OBJS)
# 	$(CC) $(CFLAGS) -o $(BUILD_DIR)/graph_algo $(GRAPH_OBJS)

test: test_graph_adj test_graph_algo

test_graph_adj: dir $(TEST_GRAPH_ADJ_OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test_graph_adj $(TEST_GRAPH_ADJ_OBJS) -lcunit

test_graph_algo: dir $(TEST_GRAPH_ALGO_OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test_graph_algo $(TEST_GRAPH_ALGO_OBJS) -lcunit

clean:
	rm -f $(foreach SRC_DIR, $(SRC_DIRS), $($(SRC_DIR))/*.o) -R build
