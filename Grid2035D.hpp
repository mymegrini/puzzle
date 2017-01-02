#ifndef GRID2035D_H
#define GRID2035D_H

#include "Grid2048D.hpp"
#include "Grid2035.hpp"

class Grid2035D : public Grid2048D, public Grid2035{

public:
  Grid2035D(int i=5, int j=5):Grid2048(i,j,"2035D"){}
  virtual int Rand() override;
};

#endif
