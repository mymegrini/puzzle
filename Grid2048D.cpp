#include "Grid2048D.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void Grid2048D::Print(){
  //*----**----**----**----*
  //|  0 || 00 || 000||0000|
  //*----**----**----**----*
  cout << endl;
  for (int i=0; i<n; ++i){
	for (int j=0; j<m; ++j)
	  cout << "*----*";
	cout << endl;
	for (int j=0; j<m; ++j){
	  Box b = Get(i,j);
	  if (b.Type() == BoxType::EMPTY)
		cout << "|    |";
	  else if (b.Type() == BoxType::CHARACTER)
		cout << "|  D |";
	  else if (b.Value()<100)
		cout << "|" << setw(3) << b.Value() << " |";
	  else
		cout << "|" << setw(4) << b.Value() << "|";
	}
	cout << endl;
	for (int j=0; j<m; ++j)
	  cout << "*----*";
	cout << endl;
  }
  cout << endl;
}

void Grid2048D::Newbox(){
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
