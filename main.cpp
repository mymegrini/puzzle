#include "main.hpp"
//#include "Box.hpp"

using namespace std;

int main(int argc, char* argv[]){

  int n = 4;
  int m = 4;
  bool text = false;
  bool human = true;
  string game = "";

  parse_argv(argc, argv, n, m, text, human, game);

  if (text){
	cout << "text-mode" << endl;
  }
  if (!human){
	cout << "auto-mode" << endl;
  }
  cout << "game: " << game << " size:" << n << 'x' << m << endl;  

  return 0;
}
