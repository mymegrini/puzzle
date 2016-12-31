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
  array[a].Value(rand24());
  array[b].Type(BoxType::INT);
  array[b].Value(rand24());
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
  int newbox;
  switch(user){
  case Input::UP :
    for(int i=1;i<n;++i){
      for(int j=0;j<m;++j){
	int k=i;
	while(Get(k-1,j).Type() == BoxType::EMPTY){
	  --k;
	  if(k==0) break;
	}
	swap(Get(i,j), Get(k,j));
	if(k!=0 &&  Get(k-1,j).Value() == Get(k,j).Value()){
	  Get(k-1,j).Value(Get(k-1,j).Value()*2);
	  Get(k,j).Type(BoxType::EMPTY);
	  Get(k,j).Value(0);
	}
      }
    }
    newbox=rand()%m;
    if(Get(n-1,newbox).Type()!=BoxType::EMPTY){
      newbox=0;
      while(newbox!=m && Get(n-1,newbox).Type()!=BoxType::EMPTY) newbox++;
    }
    Get(n-1,newbox).Type(BoxType::INT);
    Get(n-1,newbox).Value(rand24());
    break;
  case Input::DOWN :
    for(int i=n-2;i>-1;--i){
      for(int j=0;j<m;++j){
	int k=i;
	while(Get(k+1,j).Type() == BoxType::EMPTY){
	  ++k;
	  if(k==n-1) break;
	}
	swap(Get(i,j), Get(k,j));
	if(k!=n-1 &&  Get(k+1,j).Value() == Get(k,j).Value()){
	  Get(k+1,j).Value(Get(k+1,j).Value()*2);
	  Get(k,j)=Box();
	}
      }
    }
    newbox=rand()%m;
    if(Get(0,newbox).Type()!=BoxType::EMPTY){
      newbox=0;
      while(newbox!=m && Get(0,newbox).Type()!=BoxType::EMPTY) newbox++;
    }
    Get(0,newbox).Type(BoxType::INT);
    Get(0,newbox).Value(rand24());
    break;
  case Input::LEFT :
    for(int i=0;i<n;++i){
      for(int j=1;j<m;++j){
	int k=j;
	while(Get(i,k-1).Type() == BoxType::EMPTY){
	  --k;
	  if(k==0) break;
	}
	swap(Get(i,j), Get(i,k));
	if(k!=0 &&  Get(i,k-1).Value() == Get(i,k).Value()){
	  Get(i,k-1).Value(Get(i,k-1).Value()*2);
	  Get(i,k)=Box();
	}
      }
    }
    newbox=rand()%n;
    if(Get(newbox,m-1).Type()!=BoxType::EMPTY){
      newbox=0;
      while(newbox!=n && Get(newbox,m-1).Type()!=BoxType::EMPTY) newbox++;
    }
    Get(newbox,m-1).Type(BoxType::INT);
    Get(newbox,m-1).Value(rand24());
    break;
  case Input::RIGHT :
    for(int i=0;i<n;++i){
      for(int j=m-2;j>-1;--j){
	int k=j;
	while(Get(i,k+1).Type() == BoxType::EMPTY){
	  ++k;
	  if(k==m-1) break;
	}
	swap(Get(i,j), Get(i,k));
	if(k!=m-1 &&  Get(i,k+1).Value() == Get(i,k).Value()){
	  Get(i,k+1).Value(Get(i,k+1).Value()*2);
	  Get(i,k)=Box();
	}
      }
    }
    newbox=rand()%n;
    if(Get(newbox,0).Type()!=BoxType::EMPTY){
      newbox=0;
      while(newbox!=n && Get(newbox,0).Type()!=BoxType::EMPTY) newbox++;
    }
    Get(newbox,0).Type(BoxType::INT);
    Get(newbox,0).Value(rand24());
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


int Grid2048::rand24(){
  if(rand()%2 == 0) return 2;
  return 4;
}
