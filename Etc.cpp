#include "Etc.h"
#include <iostream>

MyEvent::MyEvent(UINT msg, WPARAM wParam, LPARAM lParam) :
	msg_(msg), wParam_(wParam), lParam_(lParam) 
{
	//  Nothing to do here.
}

// 이벤트가 Left 버튼이 눌러진 이벤트인가
bool MyEvent::isLButtonDownEvent() {
	return msg_ == WM_LBUTTONDOWN;
}

// Left 버튼이 떼어진 이벤트인가
bool MyEvent::isLButtonUpEvent() {
	return msg_ == WM_LBUTTONUP;
}

// R 버튼이 눌린 이벤트인가
bool MyEvent::isRButtonDownEvent() {
	return msg_ == WM_RBUTTONDOWN;
}


bool MyEvent::isRButtonUpEvent() {
	return msg_ == WM_RBUTTONUP;
}

// 이벤트 발생시 ctrl 키가 눌러져 있었는가
bool MyEvent::isCtrlKeyDown() {
	return wParam_ & MK_CONTROL;
}

// 이벤트 발생시 Shift 키가 눌러져 있었는가
bool MyEvent::isShiftKeyDown() {
	return wParam_ & MK_SHIFT;
}

// (마우스) 이벤트가 발생한 x 좌표를 구한다.
int MyEvent::getX() {
	return LOWORD(lParam_);
}

// (마우스) 이벤트가 발생한 y 좌표를 구한다.
int MyEvent::getY() {
	return HIWORD(lParam_);
}


// (마우스) 이벤트가 발생한 x,y 좌표 구조체를 가져온다.
MyPoint MyEvent::getPoint() {
	return MyPoint(LOWORD(lParam_), HIWORD(lParam_));
}

// MyPoint 클래스 함수들.
MyPoint::MyPoint(int x, int y): x_(x), y_(y){

}

MyPoint::MyPoint() : x_(0), y_(0) {

}

