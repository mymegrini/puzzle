#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "Input.hpp"
#include "Grid.hpp"

class Window {

public:
  Window(int n, int m);
  void Init();
  Input Player();
  void Render(Grid&);
  ~Window();

private:
  const int n;
  const int m;
  const int width;
  const int height;
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  void RenderBox(Box b, int x, int y);
};

#endif
