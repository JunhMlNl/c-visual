#include "MyOval.h"
#include "Graphics.h"

MyOval::MyOval(int x1, int y1, int x2, int y2, Graphics* g):MyShape(x1, y1, x2, y2, g) {
}
void MyOval::draw() {
	g_->drawOval(x_, y_, width_, height_);
}
