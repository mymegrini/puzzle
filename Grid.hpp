#ifndef GRID_H
#define GRID_H

#include <cassert>
#include "Box.hpp"
#include "Input.hpp"


class Grid { /* interface */

public:
  Grid(int n, int m, const char* name): Name(name), n(n), m(m), array(new Box[n*m]){}
  Box operator()(int i, int j){	return Get(i,j); }
  virtual void Init() = 0; // Initialize Box contents
  virtual void Start() = 0; // Start game
  virtual void Print() = 0; // Print the grid in text-mode
  virtual void Play(Input user) = 0; // Modify Grid according to user input
  virtual bool GameOver() = 0; // Returns true if game is over
  int N() { return n; }
  int M() { return m; }
  virtual ~Grid(){
	if (array != nullptr)
	  delete[] array;
  }
  const char* Name;

protected:
  int n; // Number of lines
  int m; // Number of columns
  Box* array; // Contiguous multidimentional array
  Box& Get(int i, int j){
	assert(i>=0 && i<n && "Out of bounds.");
	assert(j>=0 && j<m && "Out of bounds.");
	return array[m*i+j];
  }
};

#endif
