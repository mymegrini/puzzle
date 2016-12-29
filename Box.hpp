#ifndef BOX_H
#define BOX_H

// *----*
// |2048|
// *----*

enum class BoxType {EMPTY, INT, CHARACTER, WALL, BOX, HOLE};

class Box {

public:
  Box(BoxType t, int val): type(t), value(val){}
  BoxType Type(){ return type; }
  int Value(){ return value; }
  void Value(int v){ value = v; }
  void Type(BoxType t) { type = t; }
  
private:
  BoxType type = BoxType::EMPTY;
  int value = 0;
};

#endif
