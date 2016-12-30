CXX = g++ -std=c++14 -Wall
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
EXE = puzzle

#.SILENT	:
all 		: $(EXE)

$(EXE) 		: $(OBJ)
	$(CXX) 	-o $@ $^

main.o 		: main.hpp Box.hpp Grid.hpp GridTaquin.hpp Engine.hpp
GridTaquin.o: GridTaquin.hpp Grid.hpp Box.hpp


clean 		:
	rm -f $(OBJ)

cleanx		: clean
	rm -f $(EXE)
