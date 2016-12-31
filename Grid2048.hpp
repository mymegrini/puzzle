#ifndef GRID2048_H
#define GRID2048_H

#include "Grid.hpp"

class Grid2048 : public Grid {

public:
  Grid2048(int i=4, int j=4):Grid(i,j){}
  virtual void Init() override;
  virtual void Start() override;
  virtual void Print() override;
  virtual void Play(Input user) override;
  virtual bool GameOver() override;
  Grid2048& operator=(const Grid2048&);
  int rand24();
};

#endif
