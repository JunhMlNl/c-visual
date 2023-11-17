#pragma once
class Graphics;
class MyShape
{
protected:
	int x_, y_, width_, height_;
	Graphics* g_;
public:
	MyShape(int x1, int y1, int x2, int y2, Graphics* g);
	virtual void draw() =0 ;
};