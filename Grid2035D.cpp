#include "Grid2035D.hpp"

int Grid2035D::Rand(){
   int r = Grid2048D::Rand();
  if(r==0) return 0;
  else return Grid2035::Rand();
}
