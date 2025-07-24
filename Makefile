SRC_DIR := game
BUILD_DIR := build/debug
CC := g++
OBJ_NAME := knife_fight
INCLUDE_PATHS := -Igame -Igame/game_objects -Igame/game_buttons

SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

FRAMEWORK_PATH := -F/Library/Frameworks
FRAMEWORK_FLAGS := -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf
RPATH_FLAGS := -Wl,-rpath,/Library/Frameworks

COMPILER_FLAGS := -std=c++11 -Wall -g $(INCLUDE_PATHS) $(FRAMEWORK_PATH)
LINKER_FLAGS := $(FRAMEWORK_FLAGS) $(RPATH_FLAGS)

all: $(BUILD_DIR)/$(OBJ_NAME)

$(BUILD_DIR)/$(OBJ_NAME): $(OBJ_FILES)
	$(CC) -v $(COMPILER_FLAGS) $(OBJ_FILES) $(LINKER_FLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)