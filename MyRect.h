#pragma once
#include"MyShape.h"
class Graphics;
class MyRect: public MyShape
{
private:

public:
	MyRect(int x1, int y1, int x2, int y2, Graphics *g);
	void draw() override;
};

