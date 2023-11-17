#include "JButton.h"
#include "Globals.h"
#include <iostream>
// 함수들을 구현해야한다.

JButton::JButton() {
}

JButton::JButton(std::string title) {
	title_ = title;
}

void JButton::setBounds(int x, int y, int width, int height) {
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
}
// setLocation 은 위치를 결정하는 함수  (버튼위치만 변경)
void JButton::setLocation(int x, int y) {
	x_ = x;	
	y_ = y;
}
// setSize는 크기를 결정하는 함수  (사이즈만 변경)
void JButton::setSize(int width, int height) {
	width_ = width;
	height_ = height;
}

// 버튼을 그리는 함수
void JButton::repaint() {
	if (parent_ != nullptr && parent_->getGraphics() != nullptr) {
		Graphics* g = parent_->getGraphics();
		g->drawRect(x_, y_, width_, height_); 
		g->drawString(title_, x_ + 5 , y_ + 5); 
	}
}
// 스크린 객체 포인터를 저장하는 함수
void JButton::setParent(Screen* scr) {
	parent_ = scr;
}
// 해당 위치에 버튼이 있는지 알려주는 함수
bool JButton::areYouThere(int x, int y) {
	if (x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + height_) {
		return true;
	}
	else {
		return false;
	}
}

// 버튼 제목(명령어로 활용)을 돌려주는 함수 1109과제에는 필요 없을 것 같다.
std::string JButton::getActionString() {
	return title_;
}
// 버튼 클릭되면 자동 호출되는 함수
void JButton::onClick() {
	debugPrint(title_);
	parent_->setFigType(this);
}