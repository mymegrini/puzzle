#include "Grid2048D.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void Grid2048D::Play(Input user){
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
	  if(k!=0 &&
	     ((Get(k-1,j).Type() == BoxType::INT && Get(k-1,j).Value()==0) ||
	      (Get(k,j).Type() == BoxType::INT && Get(k,j).Value()==0))){
	    Get(k-1,j)=Box();
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
	  if(k!=n-1 &&
	     ((Get(k+1,j).Type() == BoxType::INT && Get(k+1,j).Value()==0) ||
	     (Get(k,j).Type() == BoxType::INT && Get(k,j).Value()==0))){
	    Get(k+1,j)=Box();
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
	  if(k!=0 &&
	     ((Get(i,k-1).Type() == BoxType::INT && Get(i,k-1).Value()==0) ||
	      (Get(i,k).Type() == BoxType::INT && Get(i,k).Value()==0))){
	    Get(i,k-1)=Box();
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
	  if(k!=m-1 &&
	     ((Get(i,k+1).Type() == BoxType::INT && Get(i,k+1).Value()==0) ||
	      (Get(i,k).Type() == BoxType::INT && Get(i,k).Value()==0))){
	    Get(i,k+1)=Box();
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
  if(k==0) val=0;
  array[i]=Box(BoxType::INT,val);
}
