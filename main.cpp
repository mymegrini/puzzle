#include "main.hpp"

#include "Box.hpp"
#include "GridTaquin.hpp"
#include "Grid2048.hpp"
#include "Grid2035.hpp"
#include "Grid2035D.hpp"
#include "Grid2048D.hpp"
#include "GridSokoban.hpp"
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

  if (text){

    if (game == "taquin"){
      Engine<GridTaquin> e(n,m,human);
      e.Run();
    }
    else if (game == "2048"){
      Engine<Grid2048> e(n,m,human);
      e.Run();
    }
    else if (game == "2048D"){
      Engine<Grid2048D> e(n,m,human);
      e.Run();
    }
    else if (game == "2035"){
      Engine<Grid2035> e(n,m,human);
      e.Run();
    }
    else if (game == "2035D"){
      Engine<Grid2035D> e(n,m,human);
      e.Run();
    }
    else if (game == "sokoban"){
      Engine<GridSokoban> e(n,m,human);
      e.Run();
    }
  }
  else {

    if (game == "taquin"){
      EngineSDL<GridTaquin> e(n,m,human);
      e.Run();
    }
    else if (game == "2048"){
      EngineSDL<Grid2048> e(n,m,human);
      e.Run();
    }
    else if (game == "2048D"){
      EngineSDL<Grid2048D> e(n,m,human);
      e.Run();
    }
    else if (game == "2035"){
      EngineSDL<Grid2035> e(n,m,human);
      e.Run();
    }
    else if (game == "2035D"){
      EngineSDL<Grid2035D> e(n,m,human);
      e.Run();
    }
    else if (game == "sokoban"){
	  EngineSDL<GridSokoban> e(n,m,human);
	  e.Run();
	}
  }

  return 0;
}
