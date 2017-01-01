#include "main.hpp"

#include "Box.hpp"
#include "GridTaquin.hpp"
#include "Grid2048.hpp"
#include "Engine.hpp"

#include "EngineSDL.hpp"

using namespace std;

int main(int argc, char* argv[]){

  int n = 0;
  int m = 0;
  bool text = false; //text-mode
  bool human = true; //auto-mode
  string game = ""; //game name

  parse_argv(argc, argv, n, m, text, human, game); // Defined in main.hpp
  srand(time(0)); // Seeding RNG

  if (text)

	if (game == "taquin"){
	  Engine<GridTaquin> e(n,m,human);
	  e.Run();
	}
	else if (game == "2048"){
	  Engine<Grid2048> e(n,m,human);
	  e.Run();
	}
	else if (game == "sokoban"){}
	else {}

  else

	if (game == "taquin"){
	  EngineSDL<GridTaquin> e(n,m,human);
	  e.Run();
	}
	else if (game == "2048"){
	  EngineSDL<Grid2048> e(n,m,human);
	  e.Run();
	}
	else if (game == "sokoban"){}
	else {}

  return 0;
}
