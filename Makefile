CC = gcc
CXX = g++

TARGET_EXEC := RayCast

BUILD_DIR := ./build
OBJ_DIR := $(BUILD_DIR)/obj
SRC_DIRS := ./src
INC_DIRS := ./include

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)

SRCS_BASE := $(notdir $(SRCS))
OBJS := $(SRCS_BASE:%=$(OBJ_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPP_FLAGS := $(INC_FLAGS) -MMD -MP -lSDL2

all: $(OBJS)
	$(CXX) $(OBJS) -lSDL2 -o $(BUILD_DIR)/$(TARGET_EXEC) $(LDFLAGS)

#$(BUILD_DIR)/%.c.o: $(SRC_DIRS)/%.c
#	echo $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIRS)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPP_FLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)
