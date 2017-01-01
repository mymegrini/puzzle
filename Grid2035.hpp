#ifndef GRID2035_H
#define GRID2035_H

#include "Grid2048.hpp"

class Grid2035 : public Grid2048{

public:
  Grid2035(int i=4, int j=4):Grid2048(i,j,"2048v35"){}
  virtual int Rand() override;
};
#endif
