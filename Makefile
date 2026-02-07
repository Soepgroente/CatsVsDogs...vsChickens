CXX			:= c++
CXXFLAGS	:= -std=c++20 -Wall -Wextra -Werror
INCLUDE 	:=	-I ./include \
				-I /opt/homebrew/include \
				-I ./lib/vulkan \
				-I ./lib/vectors \

LDFLAGS		=	-L/opt/homebrew/lib -lglfw -framework Cocoa -framework IOKit -framework OpenGL

SRC_DIR		:= src
BUILD_DIR	:= build
OBJ_DIR		:= $(BUILD_DIR)/obj

LIB_DIR		:= lib
VECTORLIB	:= $(LIB_DIR)/vectors
VULKANLIB	:= $(LIB_DIR)/vulkan

LIBS		:= $(VECTORLIB)/vectors.a #$(VULKANLIB)/vulkan.a

TARGET := $(BUILD_DIR)/CatsVSDogs

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

ifeq ($(UNAME_S), Linux)
	INCLUDES += -isystem $(USER)/.capt/root/usr/include
	LFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl `pkg-config --static --libs glfw3`
	BASE_CPPFLAGS += `pkg-config --cflags glfw3`
endif

all: $(TARGET)

debug: CXXFLAGS += -g -O0 -DDEBUG
debug: clean $(TARGET)

release: CXXFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)

$(VECTORLIB)/vectors.a:
	$(MAKE) -C $(LIB_DIR)/vectors

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

$(TARGET): $(LIBS) $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) $(INCLUDE) -o $(TARGET) $(LDFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(LIB_DIR)/vectors clean
# 	$(MAKE) -C $(LIB_DIR)/vulkan clean

fclean: clean
	rm -f $(TARGET)
	rm -f $(LIB_DIR)/vectors/vectors.a
# 	rm -f $(LIB_DIR)/vulkan/vulkan.a

run: $(TARGET)
	./$(TARGET)

re: fclean all

.PHONY: all debug release clean run install-deps
