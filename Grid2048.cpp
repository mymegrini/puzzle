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
  array[a]=Box(BoxType::INT,Rand());
  array[b]=Box(BoxType::INT,Rand());
}

void Grid2048::Play(Input user){
  bool hasmove=false;
  switch(user){
  case Input::UP :
    for(int i=1;i<n;++i){
      for(int j=0;j<m;++j){
	if(Get(i,j).Type() != BoxType::EMPTY){
	  int k=i;
	  while(Get(k-1,j).Type() == BoxType::EMPTY){
	    --k;
	    if(k==0) break;
	  }
	  if(k!=i){
	    hasmove=true;
	    swap(Get(i,j), Get(k,j));
	  }
	  if(k!=0 && Get(k-1,j).Value() == Get(k,j).Value()){
	    Get(k-1,j).Value(Get(k-1,j).Value()*2);
	    Get(k,j)=Box();
	    hasmove=true;
	  }
	}
      }
    }
    break;
  case Input::DOWN :
    for(int i=n-2;i>-1;--i){
      for(int j=0;j<m;++j){
	if(Get(i,j).Type() != BoxType::EMPTY){
	  int k=i;
	  while(Get(k+1,j).Type() == BoxType::EMPTY){
	    ++k;
	    if(k==n-1) break;
	  }
	  if(k!=i){
	    hasmove=true;
	    swap(Get(i,j), Get(k,j));
	  }
	  if(k!=n-1 && Get(k+1,j).Value() == Get(k,j).Value()){
	    Get(k+1,j).Value(Get(k+1,j).Value()*2);
	    Get(k,j)=Box();
	    hasmove=true;
	  }
	}
      }
    }
    break;
  case Input::LEFT :
    for(int j=1;j<m;++j){
      for(int i=0;i<n;++i){
	if(Get(i,j).Type() != BoxType::EMPTY){
	  int k=j;
	  while(Get(i,k-1).Type() == BoxType::EMPTY){
	    --k;
	    if(k==0) break;
	  }
	  if(k!=j){
	    hasmove=true;
	    swap(Get(i,j), Get(i,k));
	  }
	  if(k!=0 && Get(i,k-1).Value() == Get(i,k).Value()){
	    Get(i,k-1).Value(Get(i,k-1).Value()*2);
	    Get(i,k)=Box();
	    hasmove=true;
	  }
	}
      }
    }
    break;
  case Input::RIGHT :
    for(int j=m-2;j>-1;--j){
      for(int i=0;i<n;++i){
	if(Get(i,j).Type() != BoxType::EMPTY){
	  int k=j;
	  while(Get(i,k+1).Type() == BoxType::EMPTY){
	    ++k;
	    if(k==m-1) break;
	  }
	  if(k!=j){
	    hasmove=true;
	    swap(Get(i,j), Get(i,k));
	  }
	  if(k!=m-1 && Get(i,k+1).Value() == Get(i,k).Value()){
	    Get(i,k+1).Value(Get(i,k+1).Value()*2);
	    Get(i,k)=Box();
	    hasmove=true;
	  }
	}
      }
    }
    break;  
  default:
    ;	
  }
  if(hasmove) Newbox();
}

void Grid2048::Newbox(){
  int nbemptybox=0;
  for(int i=0; i<m*n;++i) if(array[i].Type()==BoxType::EMPTY) nbemptybox++;
  int r=rand()%nbemptybox;
  int i=-1;
  while(r>0){
    if(array[++i].Type() == BoxType::EMPTY) r--;
  }
  cout << "Case " << i << endl;
  array[i]=Box(BoxType::INT,Rand());
}

bool Grid2048::GameOver(){
  for (int i=0; i<m*n; ++i)
    if (array[i].Type()== BoxType::EMPTY)
      return false;
  for (int i=0; i<m; ++i)
	for (int j=0; j<n; ++i){
	  int k = i;
	  while (k+1<m && Get(k+1,j).Type() == BoxType::EMPTY)
		++k;
	  if (k != i && Get(i,j).Value() == Get(k,j).Value())
		return false;
	  k = i;
	  while (k>0 && Get(k-1,j).Type() == BoxType::EMPTY)
		--k;
	  if (k != i && Get(i,j).Value() == Get(k,j).Value())
		return false;
	  k = j;
	  while (k+1<n && Get(i,k+1).Type() == BoxType::EMPTY)
		++k;
	  if (k != j && Get(i,j).Value() == Get(i,k).Value())
		return false;
	  k = i;
	  while (k>0 && Get(i,k-1).Type() == BoxType::EMPTY)
		--k;
	  if (k != i && Get(i,j).Value() == Get(i,k).Value())
		return false;
	}
  return true;
}

Grid2048& Grid2048::operator=(const Grid2048& g){
  if (array != nullptr)
    delete[] array;
  n = g.n;
  m = g.m;
  array = new Box[n*m];
  for (int i=0; i<m*n; ++i)
    array[i] = g.array[i];
  return *this;
}


int Grid2048::Rand(){
  if(rand()%2 == 0) return 2;
  return 4;
}


/*
  2048 avec 2/3...

  int Grid2048::rand23(){
  int r =rand()%4; 
  if(r==0) return 2;
  if(r==1) return 4;
  if(r==2) return 3;
  return 6;
  }*/

/*if(mode=="mode23"){
  array[a]=Box(BoxType::INT,rand23());
  array[b]=Box(BoxType::INT,rand23());
  }
  if(mode=="mode235"){
  array[a]=Box(BoxType::INT,rand235());
  array[b]=Box(BoxType::INT,rand235());
  }*/
