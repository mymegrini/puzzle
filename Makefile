CXX = g++ -std=c++14 -Wall
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
EXE = puzzle
UNAME := $(shell uname -s)
SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LDFLAGS := $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image


#.SILENT	:
all 		: $(EXE)

$(EXE) 		: $(OBJ)
ifeq ($(UNAME), Darwin)
	$(CXX) 	-o $@ $^ -F/Library/Frameworks -framework SDL2 -framework SDL2_ttf -framework SDL2_image
else
	$(CXX) 	-o $@ $^ $(SDL2_LDFLAGS)
endif

Window.o	: Window.cpp Window.hpp Grid.hpp Input.hpp Texture.hpp
ifeq ($(UNAME), Darwin)
	$(CXX) -D OSX -I/Library/Frameworks/SDL2.framework/Headers -c -o $@ $<
else
	$(CXX) -c -o $@ $< $(SDL2_CFLAGS)
endif

Texture.o	: Texture.cpp Texture.hpp Box.hpp
ifeq ($(UNAME), Darwin)
	$(CXX) -D OSX -I/Library/Frameworks/SDL2.framework/Headers -c -o $@ $<
else
	$(CXX) -c -o $@ $< $(SDL2_CFLAGS)
endif


main.o 		: main.hpp Box.hpp Grid.hpp GridTaquin.hpp Engine.hpp EngineSDL.hpp
GridTaquin.o: GridTaquin.hpp Grid.hpp Box.hpp Input.hpp

clean 		:
	rm -f $(OBJ)

cleanx		: clean
	rm -f $(EXE)
