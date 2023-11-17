#pragma once
#include "Windows.h"

// 화면상의 점을 나타내는 클래스.
struct MyPoint {
	int x_, y_;
	MyPoint(int x, int y);
	MyPoint();
};

// 이벤트를 클래스화 한다.
struct MyEvent {
private:
	UINT msg_;
	WPARAM wParam_;
	LPARAM lParam_;
public:
	MyEvent(UINT msg, WPARAM wParam, LPARAM lParam);
	bool isLButtonDownEvent(); // 이벤트가 Left 버튼이 눌러진 이벤트인가
	bool isLButtonUpEvent(); // Left 버튼이 떼어진 이벤트인가
	bool isRButtonDownEvent();  // Right button
	bool isRButtonUpEvent();  // Right button

	bool isCtrlKeyDown();   // 이벤트가 들어올 때 ctrl키가 눌린 상태였는가
	bool isShiftKeyDown();  // 이벤트가 들어올 때 Shift키가 눌린 상태였는가
	int getX();
	int getY();
	MyPoint getPoint();

};

