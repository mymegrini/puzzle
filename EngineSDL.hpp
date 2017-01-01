#ifndef ENGINESDL_H
#define ENGINESDL_H

#include "Window.hpp"
#include "Engine.hpp"

template <class G>
class EngineSDL : public Engine<G> {

public:
  EngineSDL(int n, int m, bool human=true):Engine<G>(n,m,human){
	window = new Window(this->g.N(), this->g.M());
  }
  virtual ~EngineSDL(){	delete window; }

protected:
  Window* window;
  virtual void PrintGameOver(){ window->SetTitle("Game Over"); }
  virtual void Print() override { window->Render(this->g); }
  virtual void Init() override {
	window->Init(this->g.Name);
	this->g.Init();
	Print();
	SDL_Delay(1000);
	this->g.Start();
	Print();
  }
  virtual Input Player() override {

	if (this->human)
	  return window->Player();
	else
	  switch(window->Player()){
	  case Input::CLOSE :
		return Input::CLOSE;
	  default :
		return this->AutoPlayer();
	  }
  }
  virtual Input AutoPlayer() override {

	static Uint32 tick = SDL_GetTicks();
	if (SDL_GetTicks()>tick+500){
	  tick = SDL_GetTicks();
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
	} else
	  return Input::NONE;
  }
};
#endif
