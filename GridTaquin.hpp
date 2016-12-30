#ifndef GRIDTAQUIN_H
#define GRIDTAQUIN_H

#include "Grid.hpp"

class GridTaquin : public Grid {

public:
  using Grid::Grid;
  virtual void Init() override;
  virtual void Start() override;
  virtual void Print() override;
  virtual void Play(Input user) override;
  virtual bool GameOver() override;

private:
  int empty=m*n; //Location of the empty Box
};

#endif
