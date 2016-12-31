CXX = g++ -std=c++14 -Wall
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
EXE = puzzle

#.SILENT	:
all 		: $(EXE)

$(EXE) 		: $(OBJ)
	$(CXX) 	-o $@ $^ `sdl2-config --libs` -lSDL2 -lSDL2_ttf

main.o 		: main.hpp Box.hpp Grid.hpp GridTaquin.hpp Engine.hpp EngineSDL.hpp
GridTaquin.o: GridTaquin.hpp Grid.hpp Box.hpp Input.hpp
Window.o	: Window.hpp Grid.hpp Input.hpp

clean 		:
	rm -f $(OBJ)

cleanx		: clean
	rm -f $(EXE)
