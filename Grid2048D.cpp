#include "Grid2048D.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void Grid2048D::Newbox(){
  cout << "Utlise bien la fonction d'here" << endl ;
  int nbemptybox=0;
  for(int i=0; i<m*n; ++i) if(array[i].Type()== BoxType::EMPTY) nbemptybox++;
    int r=rand()%nbemptybox;
    int i=-1;
    while(r!=0){
      i++;
      if(array[i].Type()== BoxType::EMPTY) r--;
    }
    int val;
    val=Rand();
    int k=rand()%6;
    if(k==0){
      val=-1;
      array[i]=Box(BoxType::CHARACTER,val);
    }
    else array[i]=Box(BoxType::INT,val);
}
