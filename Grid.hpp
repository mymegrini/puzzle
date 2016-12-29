#ifndef GRID_H
#define GRID_H

class Grid {

public:
  virtual void Up() = 0;
  virtual void Down() = 0;
  virtual void Left() = 0;
  virtual void Right() = 0;
  virtual void print() = 0;
  virtual Box operator()(int, int) = 0;
};

#endif
