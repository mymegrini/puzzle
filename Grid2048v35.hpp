#ifndef GRID2048v35_H
#define GRID2048v35_H

#include "Grid2048.hpp"

class Grid2048v35 : public Grid2048{

public:
  Grid2048v35(int i=4, int j=4):Grid2048(i,j,"2048v35"){}
  virtual int Rand() override;
};
#endif
