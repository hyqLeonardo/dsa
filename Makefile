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
COMMON_SRC := src/dsa
TREE_SRC := src/dsa/tree
GRAPH_SRC := src/dsa/grapha
SRC_DIRS := COMMON_SRC
SRC_DIRS += TREE_SRC
SRC_DIRS += GRPH_SRC
# Direcotry to put build files
BUILD_DIR := build


##############################
# Define build targets
##############################

TREE_OBJS := $(TREE_SRC)/tree_algo.o $(COMMON_SRC)/stack.o $(COMMON_SRC)/queue.o \
	$(TREE_SRC)/bst.o $(TREE_SRC)/tbt.o

##############################
# Build
##############################
.PHONY: all

CC := gcc
CFLAGS := -Wall -g $(foreach INC_DIR, $(INC_DIRS), -I$(INC_DIR))

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

clean:
	rm -f $(foreach SRC_DIR, $(SRC_DIRS), $($(SRC_DIR))/*~) \
		$(foreach SRC_DIR, $(SRC_DIRS), $($(SRC_DIR))/*.o) -R build 
