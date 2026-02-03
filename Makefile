CXX			:= c++
CXXFLAGS	:= -std=c++23 -Wall -Wextra -Werror
INCLUDE 	:=	-I./include \
				-I/opt/homebrew/include \

LFLAGS		=	-L/opt/homebrew/lib -lglfw -framework Cocoa -framework IOKit -framework OpenGL

SRC_DIR		:= src
BUILD_DIR	:= build
OBJ_DIR		:= $(BUILD_DIR)/obj

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

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) $(INCLUDE) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

re: fclean all

.PHONY: all debug release clean run install-deps
