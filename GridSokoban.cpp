#include "GridSokoban.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void GridSokoban::Init(){
  int nbwall=rand()%((m*n)/4);
  int nbhole=rand()%((m*n)/6)+1;
  for (int i=0; i<m*n-1; ++i){
    if(i<nbwall) array[i]=Box(BoxType::WALL,0);
    else if(i<nbwall+nbhole) array[i]=Box(BoxType::HOLE,0);
    else if(i<nbwall+nbhole*2) array[i]=Box(BoxType::BOX,0);
    else array[i]=Box(BoxType::EMPTY,0);
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
		if(b.Value() == 0)
		  cout << "|" << "(  )" << "|";
		else
		  cout << "|" << "(##)" << "|";
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

void GridSokoban::Play(Input user){
  int i = character/m;
  int j = character - i*m;
  switch(user){
  case Input::UP :
    if(i!=0){
      if(Get(i-1,j).Type() == BoxType::EMPTY){
	swap(Get(i,j), Get(i-1,j));
	character-=m;
      }
      else {
	if(Get(i-1,j).Type() == BoxType::BOX){
	  if(i-1>0){
	    if(Get(i-2,j).Type() == BoxType::EMPTY){
	      swap(Get(i,j), Get(i-1,j));
	      swap(Get(i,j), Get(i-2,j));
	      character-=m;
	    }
	    else if(Get(i-2,j).Type() == BoxType::HOLE && Get(i-2,j).Value()==0){
	      Get(i-1,j)=Box();
	      swap(Get(i,j), Get(i-1,j));
	      Get(i-2,j).Value(1);
	      character-=m;
	    }
	  }
	}
      }
    }
    break;
  case Input::DOWN :
    if(i!=m-1){
      if(Get(i+1,j).Type() == BoxType::EMPTY){
	swap(Get(i,j), Get(i+1,j));
	character+=m;
      }
      else if(Get(i+1,j).Type() == BoxType::BOX){
	if(i+2<m){
	  if(Get(i+2,j).Type() == BoxType::EMPTY){
	    swap(Get(i,j), Get(i+1,j));
	    swap(Get(i,j), Get(i+2,j));
	    character+=m;
	  }
	  else if(Get(i+2,j).Type() == BoxType::HOLE && Get(i+2,j).Value()==0){
	    Get(i+1,j)=Box();
	    swap(Get(i,j), Get(i+1,j));
	    Get(i+2,j).Value(1);
	    character+=m;
	  }
	}
      }
    }
    break;
  case Input::LEFT :
    if(j!=0){
      if(Get(i,j-1).Type() == BoxType::EMPTY){
	swap(Get(i,j), Get(i,j-1));
	character--;
      }
      else if(Get(i,j-1).Type() == BoxType::BOX){
	if(j-1>0){
	  if(Get(i,j-2).Type() == BoxType::EMPTY){
	    swap(Get(i,j), Get(i,j-1));
	    swap(Get(i,j), Get(i,j-2));
	    character--;
	  }
	  else if(Get(i,j-2).Type() == BoxType::HOLE && Get(i,j-2).Value()==0){
	    Get(i,j-1)=Box();
	    swap(Get(i,j), Get(i,j-1));
	    Get(i,j-2).Value(1);
	    character--;
	  }
	}
      }
    }
    break;
  case Input::RIGHT :
    if(j!=n-1){
      if(Get(i,j+1).Type() == BoxType::EMPTY){
	swap(Get(i,j), Get(i,j+1));
	character++;
      }
      else if(Get(i,j+1).Type() == BoxType::BOX){
	if(j+2<n){
	  if(Get(i,j+2).Type() == BoxType::EMPTY){
	    swap(Get(i,j), Get(i,j+1));
	    swap(Get(i,j), Get(i,j+2));
	    character++;
	  }
	  else if(Get(i,j+2).Type() == BoxType::HOLE && Get(i,j+2).Value()==0){
	    Get(i,j+1)=Box();
	    swap(Get(i,j), Get(i,j+1));
	    Get(i,j+2).Value(1);
	    character++;
	  }
	}
      }
    }
    break;
  default:
    ;
  }
}

bool GridSokoban::GameOver(){
  for (int i=0; i<m*n; ++i)
    if (array[i].Type() == BoxType::HOLE && array[i].Value()==0)
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
