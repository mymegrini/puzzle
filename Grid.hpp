#ifndef GRID_H
#define GRID_H

#include <cassert>

enum class Input {UP, DOWN, LEFT, RIGHT}; 

class Grid { /* interface */

public:
  Grid(int n, int m):n(n), m(m), array(new Box[n*m]){}
  virtual Box operator()(int i, int j){
	assert(i>=0 && i<n && "Out of bounds.");
	assert(j>=0 && j<m && "Out of bounds.");
	return array[m*i+j];
  }
  virtual void Init() = 0; // Initialize Box contents
  virtual void play(Input user) = 0; // Modify Grid according to user input
  virtual void print() = 0; // Print the grid in text-mode
  virtual bool isOver() = 0; // Returns true if game is over
  ~Grid(){ delete[] array; }

protected:
  Box* array; // Contiguous multidimentional array
  int n; // Number of lines
  int m; // Number of columns
};

#endif
