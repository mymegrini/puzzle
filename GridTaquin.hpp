#ifndef GRIDTAQUIN_H
#define GRIDTAQUIN_H

#include "Grid.hpp"

class GridTaquin : public Grid {

public:
  GridTaquin(int i=4, int j=4):Grid(i,j){}
  virtual void Init() override;
  virtual void Start() override;
  virtual void Print() override;
  virtual void Play(Input user) override;
  virtual bool GameOver() override;
  GridTaquin& operator=(const GridTaquin&);

private:
  int empty=m*n; //Location of the empty Box
};

#endif
