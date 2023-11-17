#include "MyShape.h"
#include "Graphics.h"

MyShape::MyShape(int x1, int y1, int x2, int y2, Graphics* g):x_(min(x1, x2)), y_(min(y1, y2)),width_(abs(x1 - x2)), height_(abs(y1 - y2)), g_(g) {

}