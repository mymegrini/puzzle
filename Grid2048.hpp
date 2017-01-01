#ifndef GRID2048_H
#define GRID2048_H

#include "GridTaquin.hpp"
#include<iostream>
using namespace std;

class Grid2048 : public GridTaquin {

public:
  Grid2048(int i=4, int j=4, const char* name="2048"):GridTaquin(i,j,name){}
  virtual void Init() override;
  virtual void Start() override;
  virtual void Play(Input user) override;
  virtual bool GameOver() override;
  Grid2048& operator=(const Grid2048&);
  virtual int Rand();
  virtual void Newbox();
};

#endif
