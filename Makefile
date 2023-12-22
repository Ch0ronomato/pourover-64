V=1
SOURCE_DIR=src
BUILD_DIR=build
EXTERNAL_DIR=external
include $(N64_INST)/include/n64.mk

BOX_PATH=$(EXTERNAL_DIR)/box2d
BOX_INCLUDE=$(BOX_PATH)/include
BOX_LIB=$(BOX_PATH)/build/bin/libbox2d.a

# TODO: simplify these; compiles the box stuff
$(BOX_PATH)/src/collision/%.o: $(BOX_PATH)/src/collision/%.cpp
	@mkdir -p $(dir $@)
	@echo "    [CXX] $<"
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(BOX_PATH)/src/common/%.o: $(BOX_PATH)/src/common/%.cpp
	@mkdir -p $(dir $@)
	@echo "    [CXX] $<"
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(BOX_PATH)/src/dynamics/%.o: $(BOX_PATH)/src/dynamics/%.cpp
	@mkdir -p $(dir $@)
	@echo "    [CXX] $<"
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(BOX_PATH)/src/rope/%.o: $(BOX_PATH)/src/rope/%.cpp
	@mkdir -p $(dir $@)
	@echo "    [CXX] $<"
	$(CXX) -c $(CXXFLAGS) -o $@ $<

BOX_SRC=$(wildcard $(BOX_PATH)/src/collision/*.cpp) \
	$(wildcard $(BOX_PATH)/src/common/*.cpp) \
	$(wildcard $(BOX_PATH)/src/dynamics/*.cpp) \
	$(wildcard $(BOX_PATH)/src/rope/*.cpp)

N64_CXXFLAGS += -std=c++17
N64_CXXFLAGS += -g
N64_CXXFLAGS += -I$(BOX_PATH)/include -I$(BOX_PATH)/src
N64_CXXFLAGS += -l$(BOX_LIB)


all: $(BOX_LIB) hello.z64
.PHONY: all

       
OBJS = $(BOX_SRC:%.cpp=%.o) \
       $(BUILD_DIR)/guy.o \
       $(BUILD_DIR)/main.o \


hello.z64: N64_ROM_TITLE="Physics!"
hello.z64: $(BUILD_DIR)/hello.dfs

$(BUILD_DIR)/hello.dfs: $(wildcard filesystem/*)
$(BUILD_DIR)/hello.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)
