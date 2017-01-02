#include "GridSokoban.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void GridSokoban::Init(){
  int nbwall=rand()%((m*n)/4);
  int nbhole=rand()%((m*n)/4)+1;
  for (int i=0; i<m*n-1; ++i){
    if(i<nbwall) array[i]=Box(BoxType::WALL,0);
    else if(i<nbwall+nbhole) array[i]=Box(BoxType::HOLE,0);
    else if(i<nbwall+nbhole*2) array[i]=Box(BoxType::BOX,0);
    else array[i]=Box(BoxType::EMPTY,1);
  }
  array[m*n-1]=Box(BoxType::CHARACTER,0);
}

void GridSokoban::Start(){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(array, array+m*n, default_random_engine(seed));
  for (int i=0; i<m*n; ++i){
    if (array[i].Type() == BoxType::CHARACTER) character = i;
  }
}

void GridSokoban::Print(){
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
      if(b.Type() == BoxType::EMPTY)
	cout << "|    |";
      else if(b.Type() == BoxType::BOX)
	cout << "|" << " ## " << "|";
      else if(b.Type() == BoxType::HOLE){
		if(b.Value() == 1)
		  cout << "|" << "(##)" << "|";
		else if (b.Value() == 2)
		  cout << "|" << "<00>" << "|";
		else
		  cout << "|" << "(  )" << "|";
	  }
      else if(b.Type() == BoxType::WALL)
	cout << "|" << "||||" << "|";
      else if(b.Type() == BoxType::CHARACTER)
	cout << "|" << setw(4) << "<00>" << "|";
    }
    cout << endl;
    for (int j=0; j<m; ++j)
      cout << "*----*";
    cout << endl;
  }
  cout << endl;
}

void GridSokoban::Shift(int i, int j, bool test1, bool test2,
						int i1, int j1, int i2, int j2, int cd){

  if (Get(i,j).Type() == BoxType::CHARACTER) {
	if(test1){
	  if(Get(i+i1,j+j1).Type() == BoxType::EMPTY){
		swap(Get(i+i1,j+j1), Get(i,j));
		character+=cd;
	  }
	  else if(Get(i+i1,j+j1).Type() == BoxType::BOX){
		if(test2){
		  if(Get(i+i2,j+j2).Type() == BoxType::EMPTY){
			swap(Get(i+i2,j+j2),Get(i+i1,j+j1));
			swap(Get(i+i1,j+j1),Get(i,j));
			character+=cd;
		  }
		  else if(Get(i+i2,j+j2).Type() == BoxType::HOLE
				  && Get(i+i2,j+j2).Value()==0){
			Get(i,j) = Box(BoxType::EMPTY, 1);
			Get(i+i1,j+j1) = Box(BoxType::CHARACTER,0);
			Get(i+i2,j+j2).Value(1);
			character+=cd;
		  }
		}
	  }
	  else if(Get(i+i1,j+j1).Type() == BoxType::HOLE){
		if (Get(i+i1,j+j1).Value() == 0) {
		  Get(i,j) = Box(BoxType::EMPTY, 1);
		  Get(i+i1,j+j1).Value(2);
		  character+=cd;
		}
		else if (Get(i+i1,j+j1).Value() == 1 && test2){
		  if (Get(i+i2,j+j2).Type() == BoxType::EMPTY){
			Get(i+i2,j+j2) = Box(BoxType::BOX, 0);
			Get(i,j) = Box(BoxType::EMPTY, 1);
			Get(i+i1,j+j1).Value(2);
			character+=cd;
		  }
		  else if(Get(i+i2,j+j2).Type() == BoxType::HOLE
				  && Get(i+i2,j+j2).Value() == 0){
			Get(i+i2,j+j2).Value(1);
			Get(i,j) = Box(BoxType::EMPTY, 1);
			Get(i+i1,j+j1).Value(2);
			character+=cd;
		  }
		}
	  }
	}
  }
  else if(Get(i,j).Type() == BoxType::HOLE) {
	if(test1){
	  if(Get(i+i1,j+j1).Type() == BoxType::EMPTY){
		Get(i,j).Value(0);
		Get(i+i1,j+j1) = Box(BoxType::CHARACTER,0);
		character+=cd;
	  }
	  else if(Get(i+i1,j+j1).Type() == BoxType::BOX){
		if(test2){
		  if(Get(i+i2,j+j2).Type() == BoxType::EMPTY){
			Get(i,j).Value(0);
			Get(i+i1,j+j1) = Box(BoxType::CHARACTER,0);
			Get(i+i2,j+j2) = Box(BoxType::BOX,0);
			character+=cd;
		  }
		  else if(Get(i+i2,j+j2).Type() == BoxType::HOLE
				  && Get(i+i2,j+j2).Value()==0){
			Get(i,j).Value(0);
			Get(i+i1,j+j1) = Box(BoxType::CHARACTER,0);
			Get(i+i2,j+j2).Value(1);
			character+=cd;
		  }
		}
	  }
	  else if(Get(i+i1,j+j1).Type() == BoxType::HOLE){
		if (Get(i+i1,j+j1).Value() == 0) {
		  Get(i,j).Value(0);
		  Get(i+i1,j+j1).Value(2);
		  character+=cd;
		}
		else if (Get(i+i1,j+j1).Value() == 1 && test2){
		  if (Get(i+i2,j+j2).Type() == BoxType::EMPTY){
			Get(i+i2,j+j2) = Box(BoxType::BOX, 0);
			Get(i,j).Value(0);
			Get(i+i1,j+j1).Value(2);
			character+=cd;
		  }
		  else if(Get(i+i2,j+j2).Type() == BoxType::HOLE
				  && Get(i+i2,j+j2).Value() == 0){
			Get(i+i2,j+j2).Value(1);
			Get(i,j).Value(0);
			Get(i+i1,j+j1).Value(2);
			character+=cd;
		  }
		}
	  }
	}
  }
  return;
}

void GridSokoban::Play(Input user){
  int i = character/m;
  int j = character - i*m;
  switch(user){
  case Input::UP :
	Shift(i,j, i>0,i-1>0, -1,0, -2,0, -m);
	break;
  case Input::DOWN :
	Shift(i,j, i<m-1,i-1<m-1, 1,0, 2,0, m);
    break;
  case Input::LEFT :
	Shift(i,j, j>0, j-1>0, 0,-1, 0,-2, -1);
    break;
  case Input::RIGHT :
	Shift(i,j, j<n-1, j+1<n-1, 0,1, 0,2, 1);
    break;
  default:
    ;
  }
}

bool GridSokoban::GameOver(){
  for (int i=0; i<m*n; ++i)
    if (array[i].Type() == BoxType::HOLE && array[i].Value()!=1)
      return false;
  return true;
}

GridSokoban& GridSokoban::operator=(const GridSokoban& g){
  if (array != nullptr)
    delete[] array;
  n = g.n;
  m = g.m;
  array = new Box[n*m];
  character = g.character;
  for (int i=0; i<m*n; ++i)
    array[i] = g.array[i];
  return *this;
}
