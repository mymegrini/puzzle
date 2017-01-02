#ifndef GRID2035D_H
#define GRID2035D_H

#include "Grid2048D.hpp"

class Grid2035D : public Grid2048D{

public:
  Grid2035D(int i=4, int j=4):Grid2048D(i,j,"2035D"){}
  virtual int Rand() override;
};
#endif
