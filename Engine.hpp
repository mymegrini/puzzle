#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "Input.hpp"

template <class G>
class Engine {

public:
  Engine(int n, int m, bool human=true):human(human){
	if (n*m == 0)
	  g = G();
	else
	  g = G(n,m);
	g.Init();
	g.Print();
  }

  virtual void Run(){

	g.Start();
	g.Print();
	while(!g.GameOver()){
	  g.Play(Player());
	  g.Print();
	}
  }

  virtual Input Player(){

	if(human){
	  string input;
	  cin >> input;
	  switch(input[0]){
	  case 'w' :
		return Input::UP;
	  case 'a' :
		return Input::LEFT;
	  case 's' :
		return Input::DOWN;
	  case 'd' :
		return Input::RIGHT;
	  case 'c' :
		exit(0);
	  default :
		return Input::UNHANDLED;
	  }
	}
	else {
	  using namespace std::chrono_literals;
	  std::chrono::high_resolution_clock::now();
	  std::this_thread::sleep_for(2s);
	  std::chrono::high_resolution_clock::now();

	  switch(rand() % 4){
	  case 0 :
		return Input::UP;
	  case 1 :
		return Input::LEFT;
	  case 2 :
		return Input::DOWN;
	  case 3 :
		return Input::RIGHT;
	  default :
		return Input::UNHANDLED;
	  } 
	}
  }
private:
  bool human;
  G g;
};
	
#endif
