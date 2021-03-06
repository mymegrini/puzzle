#include "Window.hpp"
#include "Texture.hpp"

#include <iostream>
#include <string>

using namespace std;

#define BOX_SIZE 90
#define BOX_BORDER (BOX_SIZE/20)
#define BOX_INNER_SIZE (BOX_SIZE-2*BOX_BORDER)
#define MARGIN (BOX_SIZE/2)

#define BLACK 0, 0, 0, 200
#define GRAY 200, 200, 200, 200
#define WHITE 240, 240, 255, 255

Window::Window(int n, int m): n(n), m(m), width(BOX_SIZE*m+2*MARGIN-BOX_BORDER),
							  height(BOX_SIZE*n+2*MARGIN-BOX_BORDER){}

void Window::Init(const char* title) {

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
	cerr << "SDL could not initialize! SDL_Error: ";
	cerr << SDL_GetError() << endl;
	return;
  }

  //Create window
  window =
	SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					 width, height,	SDL_WINDOW_SHOWN );

  if( window == NULL ) {
	cerr << "Window could not be created! SDL_Error:";
	cerr << SDL_GetError() << endl;
	return;
  }

  //Set Icon
  SDL_Surface* icon = IMG_Load("assets/Icon.png");
  if (icon == NULL){
	cerr << "Couldn't load image (assets/Icon.png). SDL_Error: ";
	cerr << SDL_GetError() << endl;
  }
  SDL_SetWindowIcon(window, icon);
  SDL_FreeSurface(icon);

  //get renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC |
								SDL_RENDERER_ACCELERATED);

  if( renderer == NULL ) {
	cerr << "Renderer could not be created! SDL_Error: ";
	cerr << SDL_GetError() << endl;
	return;
  }

  Texture::Init(renderer);
}

Input Window::Player(){

  SDL_Event event;

  while(SDL_WaitEventTimeout(&event, 50)) {
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
	  return Input::NONE;
	}
	SDL_PumpEvents();
  }
  return Input::NONE;
}

void Window::Render(Grid& g){

  SDL_SetRenderDrawColor(renderer, WHITE);
  SDL_RenderClear(renderer);
  if (string(g.Name) == string("Sokoban")){
	SDL_SetRenderDrawColor(renderer, GRAY);
	SDL_Rect border = {MARGIN-BOX_BORDER, MARGIN-BOX_BORDER,
					   g.N()*BOX_SIZE, g.M()*BOX_SIZE};
	SDL_RenderDrawRect(renderer, &border);
  }
  SDL_SetRenderDrawColor(renderer, BLACK);
  for (int i=0; i<n; ++i)
	for(int j=0; j<m; ++j)
	  RenderBox(g(i,j), j*BOX_SIZE+MARGIN, i*BOX_SIZE+MARGIN);
  SDL_RenderPresent(renderer);
}

void Window::RenderBox(Box b, int x, int y){

  int w = BOX_INNER_SIZE;
  int h = BOX_INNER_SIZE;
  SDL_Point centre = { x+BOX_INNER_SIZE/2, y+BOX_INNER_SIZE/2 };
  SDL_Rect box = { x, y, BOX_INNER_SIZE, BOX_INNER_SIZE };
  Texture texture(b);

  switch(b.Type()){
  case BoxType::EMPTY :
	if(b.Value() != 1){
	  SDL_SetRenderDrawColor(renderer, GRAY);
	  SDL_RenderDrawRect(renderer, &box);
	  SDL_SetRenderDrawColor(renderer, BLACK);
	}
	return;
  case BoxType::INT :
	if (b.Value() == 0){
	  SDL_RenderFillRect(renderer, &box);
	  return;
	} else {
	  int color = b.Value();
	  SDL_SetRenderDrawColor(renderer, 255-color/16, 255-16*((color/16) % 16),
							 255-16*(color % 16), 200);
	  SDL_RenderFillRect(renderer, &box);
	  SDL_SetRenderDrawColor(renderer, BLACK);
	}

	SDL_RenderDrawRect(renderer, &box);
	h /= 2;
  default :
	texture.RenderFit(w, h, &centre);
	return;
  }
}

void Window::SetTitle(const char* title){ SDL_SetWindowTitle(window, title); }

Window::~Window(){

  //Free static textures
  Texture::Free();

  //Shut down SDL_ttf
  TTF_Quit();

  //Destroy renderer
  SDL_DestroyRenderer( renderer );

  //Destroy window
  SDL_DestroyWindow( window );

  //Quit SDL subsystems
  SDL_Quit();
}
