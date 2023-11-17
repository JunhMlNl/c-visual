#pragma once
#include"MyShape.h"
class Graphics;
class MyOval: public MyShape
{
private:
	
public:
	MyOval(int x1, int y1, int x2, int y2, Graphics* g);
	void draw()override;
};
