#ifndef GRIDSOKOBAN_H
#define GRIDSOKOBAN_H

#include "Grid.hpp"

class GridSokoban : public Grid {

public:
  GridSokoban(int i=4, int j=4, const char* name = "Sokoban"):Grid(i,j,name){}
  virtual void Init() override;
  virtual void Start() override;
  virtual void Print() override;
  virtual void Play(Input user) override;
  virtual bool GameOver() override;
  GridSokoban& operator=(const GridSokoban&);

private :
  int character=0; //location of the character
};

#endif
