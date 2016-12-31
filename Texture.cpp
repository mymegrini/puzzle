#include "Texture.hpp"
#include <iostream>
#include "Box.hpp"

using namespace std;

SDL_Renderer* Texture::renderer = NULL;
SDL_Texture* Texture::character = NULL;
SDL_Texture* Texture::crate = NULL;
SDL_Texture* Texture::hole = NULL;
SDL_Texture* Texture::filledhole = NULL;
SDL_Texture* Texture::wall = NULL;
TTF_Font* Texture::font = NULL;
SDL_Color Texture::black = {0,0,0};
SDL_Color Texture::white = {255,255,255};

Texture::Texture(Box& b):box(b){

  if (box.Type() == BoxType::INT){
	string tmp = std::to_string(b.Value());
	const char* number = tmp.c_str();
	SDL_Surface* surface = TTF_RenderText_Solid(font, number, black);
	width = surface->w;
	height = surface->h;
	text = SDL_CreateTextureFromSurface(renderer, surface);
	if (text == NULL){
	  cerr << "Unable to create texture from TTF text. SDL Error: ";
	  cerr << SDL_GetError() << endl;
	}	
	SDL_FreeSurface(surface);
  }
}

void Texture::Init(SDL_Renderer* r){

  renderer = r;
  if( TTF_Init() == -1){
	cerr << "Failed to initialize TTF library. SDL_Error: ";
	cerr << SDL_GetError() << endl;
  }	else {
	font = TTF_OpenFont("assets/Squareo.ttf", 40);
	if( font == NULL ) {
	  cerr << "Couldn't open ttf font. SDL_Error: ";
	  cerr << SDL_GetError() << endl;
	}
  }
  LoadImage("assets/coin_gold.png", &filledhole);
  LoadImage("assets/crate.png", &wall);
  LoadImage("assets/front.png", &character);
  LoadImage("assets/key_yellow.png", &crate);
  LoadImage("assets/lock_yellow.png", &hole);
}

void Texture::LoadImage(const char* path, SDL_Texture** target){

  SDL_Surface* image = IMG_Load(path);
  if (image == NULL){
	cerr << "Couldn't load image (" << path << "). SDL_Error: ";
	cerr << SDL_GetError() << endl;
  }
  *target = SDL_CreateTextureFromSurface(renderer, image);
  if (*target == NULL){
	cerr <<"Couldn't create Texture from image (" <<path <<"). SDL_Error: ";
	cerr <<SDL_GetError() << endl;
  }
  SDL_FreeSurface(image);  
}

void Texture::Free(){

  renderer = NULL;
  SDL_DestroyTexture(character);
  character = NULL;
  SDL_DestroyTexture(crate);
  crate = NULL;
  SDL_DestroyTexture(hole);
  hole = NULL;
  SDL_DestroyTexture(filledhole);
  filledhole = NULL;
  SDL_DestroyTexture(wall);
  wall = NULL;
  TTF_CloseFont(font);
  font = NULL;
}
  
void Texture::RenderFit(int w, int h, SDL_Point* center){

  double ratio = min((double)w/width, (double)h/height);
  int newh = (int)((double)height*ratio/2.+.5);
  int neww = (int)((double)width*ratio/2.+.5);
  SDL_Rect target = { center->x - neww, center->y - newh,
					  2*neww, 2*newh };
  SDL_Texture* texture = NULL;
  switch(box.Type()){
  case BoxType::INT:
	texture = text;
	break;
  case BoxType::CHARACTER:
	texture = character;
	break;
  case BoxType::BOX:
	texture = crate;
	break;
  case BoxType::HOLE:
	texture = (box.Value()==0?hole:filledhole);
	break;
  case BoxType::WALL:
	texture = wall;
	break;
  default :
	texture = NULL;
  }
  if(texture!=NULL)
	SDL_RenderCopy(renderer, texture, NULL, &target);
}

Texture::~Texture(){
  if (text != NULL){
	SDL_DestroyTexture(text);
	text = NULL;
	width = 0;
	height = 0;
  }
}
