#ifndef BOX_H
#define BOX_H

#include <iostream>

// *------*
// |      |
// | 2048 |
// |      |
// *------*

enum class BoxType {EMPTY, INT, CHARACTER, WALL, BOX, HOLE};

class Box {

public:
  Box(BoxType t, int val): type(t), value(val){}
  BoxType Type(){ return type; }
  BoxType value(){ return value; }

private:
  BoxType type = BoxType::EMPTY;
  int value = 0;

  friend ostream& operator<<(ostream&, Box& b);
};

#endif
