#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "Input.hpp"

using namespace std::chrono_literals;

template <class G>
class Engine {

public:
  Engine(int n, int m, bool human=true):human(human){
    if (n*m == 0)
      g = G();
    else
      g = G(n,m);
  }

  virtual void Run(){

	Init();
	while(!g.GameOver()){
	  Input input = Player();
	  switch(input){
	  case Input::CLOSE:
		return;
	  case Input::NONE:
		break;
	  default :
		g.Play(input);
	  }
	  Print();
	}
	PrintGameOver();
	while(true){
	  Input input = Player();
	  switch(input){
	  case Input::CLOSE:
		return;
	  default:
		;
	  }
	}
  }

protected:
  virtual void PrintGameOver(){ cout << "Game over." << endl; }
  virtual void Print(){ g.Print(); }
  virtual void Init(){
	g.Init();
	Print();
	std::this_thread::sleep_for(2s);
	g.Start();
	Print();	
  }
  virtual Input Player(){

    if(human){
      string input;
      cin >> input;
      switch(input[0]){
      case 'w' :
	return Input::UP;
      case 'z' :
	return Input::UP;
      case 'a' :
	return Input::LEFT;
      case 'q' :
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
    else
      return AutoPlayer();
  }
  virtual Input AutoPlayer(){
	std::this_thread::sleep_for(500ms);
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
  bool human;
  G g;
};
	
#endif
