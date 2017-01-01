#include "Grid2035.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;


int Grid2035::Rand(){
  int r =rand()%6; 
  if(r==0) return 2;
  if(r==1) return 4;
  if(r==2) return 3;
  if(r==3) return 6;
  if(r==4) return 5;
  return 10;
}
