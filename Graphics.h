#pragma once
#include "Windows.h"
#include <string>
class Graphics
{
public:
	Graphics(HDC);
	
	// 그리기 함수들은 Java의 그리기 함수를 흉내낸 것.
	// 
	// 사각형 그리기
	void drawRect(int x, int y, int width, int height);
	
	// 타원 그리기
	void drawOval(int x, int y, int width, int height);
	
	// 선분 그리기
	//void drawLine(int x1, int y1, int x2, int y2);
	
	// 텍스트 그리기
	void drawString(std::string s, int x, int y);
	
	// 선 색 지정하기
	//void setColor(Color c);

	// 바탕색 지정하기
	//void setFillColor(Color c);
private:
	HDC hDC_;
};

