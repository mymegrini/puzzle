#ifndef GRID2048D_H
#define GRID2048D_H

#include "Grid2048.hpp"

class Grid2048D : virtual public Grid2048{

public:
  Grid2048D(int i=4, int j=4, const char* name="2048D"):Grid2048(i,j,name){}
  virtual void Play(Input user) override;
  virtual void Newbox() override;
};
#endif
