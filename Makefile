V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

N64_CXXFLAGS += -std=c++17
N64_CXXFLAGS += -g


all: hello.z64
.PHONY: all

OBJS = $(BUILD_DIR)/guy.o $(BUILD_DIR)/main.o 

hello.z64: N64_ROM_TITLE="Drawing"
hello.z64: $(BUILD_DIR)/hello.dfs

$(BUILD_DIR)/hello.dfs: $(wildcard filesystem/*)
$(BUILD_DIR)/hello.elf: $(OBJS)

$(BUILD_DIR)/hello.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)
