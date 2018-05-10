TITLE   	 = zombie
CXX      	= g++
STANDARD 	= -std=c++17
DEBUG    	= -g
INCLUDE  	= -I./include
WFLAGS   	= -Wall -Wextra -O2
CXXFLAGS 	= $(WFLAGS) $(STANDARD) $(INCLUDE) $(DEBUG)
LDFLAGS 	= -lm
OPENGL_FLAGS    = -lGL -lGLU -lglut
SFML_FLAGS      = -ltgui -lsfml-graphics -lsfml-window -lsfml-system
BIN		= build
MAIN		= main.cpp
MAINOBJ 	= $(BIN)/$(MAIN:.cpp=.o)
SRC 		= $(wildcard src/*.cpp)
HEAD 		= $(patsubst src/%.cpp, include/%.h, $(SRC))
HEADONLY 	= $(wildcard include/*.h)
OBJ 		= $(patsubst src/%.cpp, $(BIN)/%.o, $(SRC))
TARGET 		= $(BIN)/$(TITLE)



.PHONY: clean zip beauty

all: $(BIN) $(TARGET)

$(TARGET): $(OBJ) $(MAINOBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(OPENGL_FLAGS) $(SFML_FLAGS)

$(MAINOBJ): $(MAIN) $(HEADONLY)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN)/%.o: src/%.cpp include/%.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN):
	@test ! -d $@ && mkdir $@

clean:
	rm -rf $(BIN)
	rm -f ~*

zip:
	zip -r $(TITLE).zip ./

beauty:
	-indent -kr -ci2 -cli2 -i2 -l80 -nut *.cpp *.hpp
