#include "Grid2035D.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int Grid2035D::Rand(){
   int r = Grid2048D::Rand();
  if(r==0) return 0;
  else return Grid2035::Rand();
}
