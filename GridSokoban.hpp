#ifndef GRIDSOKOBAN_H
#define GRIDSOKOBAN_H

#include "Grid.hpp"

class GridSokoban : public Grid {

public:
  GridSokoban(int i=10, int j=10, const char* name = "Sokoban"):Grid(i,j,name){}
  virtual void Init() override;
  virtual void Start() override;
  virtual void Print() override;
  virtual void Play(Input user) override;
  virtual bool GameOver() override;
  GridSokoban& operator=(const GridSokoban&);

private :
  int character=0; //location of the character
  void Shift(int, int, bool, bool, int, int, int, int, int); 
};

#endif
