#include "Grid2048.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void Grid2048::Init(){
}

void Grid2048::Start(){
  int a(rand()%(m*n)),b(rand()%(m*n));
  while(a==b) b=rand()%(m*n);
  array[a].Type(BoxType::INT);
  array[a].Value(2);
  array[b].Type(BoxType::INT);
  array[b].Value(4);
  //unsigned seed = chrono::system_clock::now().time_since_epoch().count();
}

void Grid2048::Print(){

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


void Grid2048::Play(Input user){
  /*array[i-1].Type(BoxType::INT);
    array[i-1].Value(i);
    int i = empty/m;
    int j = empty - i*m;
  
    assert(Get(i,j).Type()==BoxType::EMPTY && "Empty index is corrupted.");*/
  switch(user){
  case Input::UP :
    for(int i=1;i<n;++i){
      for(int j=0;i<m;++j){
	if(Get(i-1,j).Type() == BoxType::EMPTY){
	  swap(Get(i,j), Get(i-1,j));
	  if(Get(i-1,j).Value() == Get(i,j).Value()){
	    Get(i-1,j).Value(pow(Get(i-1,j).Value(),2));
	    Get(i,j).Type(BoxType::EMPTY);
	  }
	}
      }
    }
    break;
  case Input::DOWN :
    for(int i=n-1;i>-1;--i){
      for(int j=0;j<m;++j){
	if(Get(i+1,j).Type() == BoxType::EMPTY){
	  swap(Get(i,j), Get(i+1,j));
	  if(Get(i+1,j).Value() == Get(i,j).Value()){
	    Get(i+1,j).Value(pow(Get(i+1,j).Value(),2));
	    Get(i,j).Type(BoxType::EMPTY);
	  }
	}
      }
    }
    break;
  case Input::LEFT :
    for(int i=0;i<n;++i){
      for(int j=1;j<m;++j){
	if(Get(i,j-1).Type() == BoxType::EMPTY){
	  swap(Get(i,j), Get(i,j-1));
	  if(Get(i,j-1).Value() == Get(i,j).Value()){
	    Get(i,j-1).Value(pow(Get(i,j-1).Value(),2));
	    Get(i,j).Type(BoxType::EMPTY);
	  }
	}
      }
    }
    break;
  case Input::RIGHT :
    for(int i=0;i<n;++i){
      for(int j=m-1;j>-1;--j){
	if(Get(i,j+1).Type() == BoxType::EMPTY) {
	  swap(Get(i,j), Get(i,j+1));
	  if(Get(i,j+1).Value() == Get(i,j).Value()){
	    Get(i,j+1).Value(pow(Get(i,j+1).Value(),2));
	    Get(i,j).Type(BoxType::EMPTY);
	  }
	}
      }
    }
    break;
  default:
    ;
	
  }
}

bool Grid2048::GameOver(){

  for (int i=0; i<m*n; ++i)
    if (array[i].Type()== BoxType::EMPTY)
      return false;
  return true;
}

Grid2048& Grid2048::operator=(const Grid2048& g){

  if (array != nullptr)
    delete[] array;

  n = g.n;
  m = g.m;
  array = new Box[n*m];
  // empty = g.empty;
  for (int i=0; i<m*n; ++i)
    array[i] = g.array[i];
  return *this;
}
