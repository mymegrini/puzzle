#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#ifndef OSX
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#endif

#include "Box.hpp"

class Texture {

public:
  Texture(Box& b);
  virtual void RenderFit(int width, int height, SDL_Point* center);
  virtual int Width(){ return width; }
  virtual int Height(){ return height; }
  static void Init(SDL_Renderer* r);
  static void Free();
  virtual ~Texture();

private:
  Box& box;
  int width = 1;
  int height = 1;
  SDL_Texture* text = NULL;
  static SDL_Renderer* renderer;
  static SDL_Texture* character;
  static SDL_Texture* crate;
  static SDL_Texture* hole;
  static SDL_Texture* filledhole;
  static SDL_Texture* wall;
  static SDL_Texture* characteroverhole;
  static TTF_Font* font;
  static SDL_Color black;
  static SDL_Color white;
  static void LoadImage(const char* path, SDL_Texture** target);
};

#endif
