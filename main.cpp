#include "main.hpp"

#include "Box.hpp"
#include "GridTaquin.hpp"
#include "Game.hpp"

using namespace std;

int main(int argc, char* argv[]){

  bool text = false; //text-mode
  bool human = true; //auto-mode
  string game = ""; //game name

  parse_argv(argc, argv, n, m, text, human, game); // Defined in main.hpp

  cout << "game: " << game << " size:" << n << 'x' << m;
  if (text)
	cout << " text-mode";
  if (!human)
	cout << " auto-mode";
  cout << endl;

  Box b = {BoxType::EMPTY, 7};
  Box a = b;
  cout << "Box a(" << a.Value() << ")" << endl;

  if (game == "taquin"){
	GridTaquin g(n, m);
	g.Init();
	g.Shuffle();
	g.Print();
	g.Play(Input::UP);
	g.Print();
	g.Play(Input::LEFT);
	g.Print();
	g.Play(Input::DOWN);
	g.Print();
	g.Play(Input::RIGHT);
	g.Print();
  }

  return 0;
}
