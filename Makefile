SRC_DIR=src
BUILD_DIR=build
BINARY=chess

CXX=g++
GDB=gdb
MKDIR=mkdir -p

LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
.PHONY: all run debug clean
all: compile

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BINARY): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

compile:
	$(MKDIR) $(BUILD_DIR)
	$(MAKE) $(BINARY)

run: compile
	./$(BINARY)


#-include $(OBJECT_FILES:.o=.d)
