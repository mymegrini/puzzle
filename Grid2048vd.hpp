#ifndef GRID2048vd_H
#define GRID2048vd_H

#include "Grid2048.hpp"

class Grid2048vd : public Grid2048{

public:
  Grid2048vd(int i=4, int j=4):Grid2048(i,j,"2048vd"){}
  virtual void Newbox() override;
};
#endif
