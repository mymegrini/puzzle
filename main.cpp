#include "main.hpp"

#include "Box.hpp"

using namespace std;

int main(int argc, char* argv[]){

  int n = 4; //number of columns
  int m = 4; //number of lines
  bool text = false; //text-mode
  bool human = true; //auto-mode
  string game = ""; //game name

  parse_argv(argc, argv, n, m, text, human, game);

  if (text); //text-mode
  if (!human); //auto-mode
  cout << "game: " << game << " size:" << n << 'x' << m << endl;

  Box b = {BoxType::EMPTY, 7};
  Box a = b;
  cout << "Box a(" << a.Value() << ")" << endl; 
  

  return 0;
}
