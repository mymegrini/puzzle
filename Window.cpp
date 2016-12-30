#include "Window.hpp"

#include <iostream>
using namespace std;

#define BOX_SIZE 50
#define BOX_BORDER 2
#define BOX_WIDTH (BOX_SIZE-2*BOX_BORDER)

#define BLACK 255, 0, 0, 0
#define WHITE 255, 255, 255, 255

Window::Window(int n, int m): n(n), m(m), width(BOX_SIZE*(n+2)),
							  height(BOX_SIZE*(m+2)){}

void Window::Init() {

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
	cerr << "SDL could not initialize! SDL_Error: ";
	cerr << SDL_GetError() << endl;
	return;
  }

  //Create window
  window =
	SDL_CreateWindow("Puzzle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					 width, height,	SDL_WINDOW_BORDERLESS|SDL_WINDOW_SHOWN );

  if( window == NULL ) {
	cerr << "Window could not be created! SDL_Error:";
	cerr << SDL_GetError() << endl;
	return;
  }

  //get Renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC |
								SDL_RENDERER_ACCELERATED);

  if( renderer == NULL ) {
	cerr << "Renderer could not be created! SDL_Eroor: ";
	cerr << SDL_GetError() << endl;
	return;
  }
}

Input Window::Player(){

  SDL_Event event;

  while(SDL_PollEvent(&event)) {
	switch(event.type){
	case SDL_QUIT :
	  return Input::CLOSE;
	case SDL_KEYDOWN :
	  switch (event.key.keysym.sym){
	  case SDLK_LEFT:  return Input::LEFT;
	  case SDLK_RIGHT: return Input::RIGHT;
	  case SDLK_UP:    return Input::UP;
	  case SDLK_DOWN:  return Input::DOWN;
	  default :
		return Input::UNHANDLED;
	  }
	  break;
	default :
	  return Input::UNHANDLED;
	}
  }
  return Input::NONE;
}

void Window::Render(Grid& g){

  SDL_SetRenderDrawColor(renderer, WHITE);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, BLACK);
  for (int i=0; i<n; ++i)
	for(int j=0; j<m; ++j)
	  RenderBox(g(i,j), (i+1)*BOX_SIZE, (j+1)*BOX_SIZE);
}

void Window::RenderBox(Box b, int x, int y){

  //Drawing square
  SDL_Rect box = { x, y, BOX_WIDTH, BOX_WIDTH };
  SDL_RenderDrawRect(renderer, &box);
}

Window::~Window(){

  //Destroy renderer
  SDL_DestroyRenderer( renderer );
  renderer = NULL;

  //Destroy window
  SDL_DestroyWindow( window );
  window = NULL;

  //Quit SDL subsystems
  SDL_Quit();
}
