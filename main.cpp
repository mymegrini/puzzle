#include "main.hpp"

#include "Box.hpp"
#include "GridTaquin.hpp"
#include "Engine.hpp"

using namespace std;

int main(int argc, char* argv[]){

  int n = 0;
  int m = 0;
  bool text = false; //text-mode
  bool human = true; //auto-mode
  string game = ""; //game name

  parse_argv(argc, argv, n, m, text, human, game); // Defined in main.hpp
  srand(time(0)); // Seeding RNG

  cout << "game: " << game << " size:" << n << 'x' << m;
  if (text)
	cout << " text-mode";
  if (!human)
	cout << " auto-mode";
  cout << endl;

  Box b = {BoxType::EMPTY, 7};
  Box a = b;
  cout << "Box a(" << a.Value() << ")" << endl;

  string s;
  cout << "Testing cin : ";
  cin >> s;
  cout << s << endl;

  if (game == "taquin"){
	Engine<GridTaquin> e(n,m,human);
	e.Run();
  }

  return 0;
}
