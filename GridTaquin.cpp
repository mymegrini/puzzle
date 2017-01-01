#include "GridTaquin.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void GridTaquin::Init(){
  for (int i=1; i<m*n; ++i){
	array[i-1].Type(BoxType::INT);
	array[i-1].Value(i);
  }
}

void GridTaquin::Start(){
  
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(array, array+m*n, default_random_engine(seed));
  for (int i=0; i<m*n; ++i)
	if (array[i].Type() == BoxType::EMPTY)
	  empty = i;
}

void GridTaquin::Print(){

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

void GridTaquin::Play(Input user){

  int i = empty/m;
  int j = empty - i*m;
  assert(Get(i,j).Type()==BoxType::EMPTY && "Empty index is corrupted.");
  switch(user){
  case Input::UP :
	if (i+1<n){
	  swap(Get(i,j), Get(i+1,j));
	  empty += m;
	}
	break;
  case Input::DOWN :
	if (i>0){
	  swap(Get(i,j), Get(i-1,j));
	  empty-=m;
	}
	break;
  case Input::LEFT :
	if (j+1<m){
	  swap(Get(i,j), Get(i,j+1));
	  empty+=1;
	}
	break;
  case Input::RIGHT :
	if (j>0){
	  swap(Get(i,j), Get(i,j-1));
	  empty-=1;
	}
	break;
  default:
	;
  }
}

bool GridTaquin::GameOver(){

  for (int i=1; i<m*n; ++i)
	if (array[i-1].Value() != i)
	  return false;
  return true;
}

GridTaquin& GridTaquin::operator=(const GridTaquin& g){

  if (array != nullptr)
	delete[] array;

  n = g.n;
  m = g.m;
  array = new Box[n*m];
  empty = g.empty;
  for (int i=0; i<m*n; ++i)
	array[i] = g.array[i];
  return *this;
}
