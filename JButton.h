#pragma once
#include <string>
#include "Screen.h"
class JButton
{
public:
	JButton();
	JButton(std::string title);

	// setBounds 함수는 위치와 크기를 설정하는 함수. (버튼의 크기)
	void setBounds(int x, int y, int width, int height); 

	// setLocation 은 위치를 결정하는 함수  (버튼위치만 변경)
	void setLocation(int x, int y);

	// setSize는 크기를 결정하는 함수  (사이즈만 변경)
	void setSize(int width, int height);

	void repaint();			// 버튼을 그리는 함수   
	void setParent(Screen*);		// 스크린 객체 포인터를 저장하는 함수
	bool areYouThere(int x, int y);  // 해당 위치에 버튼이 있는지 알려주는 함수
	std::string getActionString();	// 버튼 제목(명령어로 활용)을 돌려주는 함수 1109과제에는 필요 없을 것 같다.
	void onClick();			// 버튼 클릭되면 자동 호출되는 함수

protected:  // 나중에 상속을 위해서 protected로 해두자.
	std::string title_;	// 버튼 제목
	int x_, y_, width_, height_;  // 위치 및 크기
	Screen* parent_;				// screen에 대한 포인터.

};

