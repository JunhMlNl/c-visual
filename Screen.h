#pragma once
#include "Windows.h"
#include <string>
#include <list>
#include "Etc.h"
#include "Graphics.h"
#include"MyShape.h"
#include "MyRect.h"
#include "MyOval.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class JButton;
class Screen {
protected:
	// Window 프로그래밍을 위한 기본 변수들이다. 건드리지 않는다.
	HINSTANCE hInst_;
	HWND hWnd_;	 // 윈도 핸들을 저장해둔다.
	HDC hDC_;    // 이 변수가 있어야 그림을 그릴 수 있다.
	Graphics * graphics_ ;
public:
	static Screen* mainScreen;	// 전역 변수 대신 static 으로 한다.

	Screen();
	Screen(std::wstring, int, int);
	virtual void eventLoop();

	Graphics * getGraphics() ;
	virtual bool eventHandler( MyEvent e);
	virtual void repaint();
	void invalidate();	// 현재의 화면이 다시 그려져야하는 상태임을 알림.
	virtual void initialize() ;  // Must override
	void setFigType(JButton *);	
	
	// GUI 를 위한 함수
	void addButton(JButton*);
	JButton * findButton(MyEvent e);	// 버튼의 areYouThere 함수를 이용해서 찾는 함수

private:
	// GUI를 위한 변수 선언
	JButton* button_[100];
	int numButtons = 0;

	JButton* tempBtn = nullptr; //클릭했을때 tempBtn에 저장하고 클릭을 띄었을때 클릭했을때의 버튼과 동일한가 다른가를 판단할 때 사용한 변수.
	// 응용을 위한 변수 선언
private:
	MyShape* myshape[100]; //도형객체
	int numShape = 0; //도형개수 
	MyRect* rect; //임시 사각형 객체
	MyOval* oval; //임시 타원 객체
	// 임시 변수
	int startx, starty, endx, endy;
	int figType_ = 0;  //0이면 사각형 선택, 1이면 타원 선택으로 사용.
public:
	void onLButtonDown(MyEvent e);
	void onLButtonUp(MyEvent e);
};