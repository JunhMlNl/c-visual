#include "Screen.h"
#include "Etc.h"
#include "JButton.h"
#include <iostream>



Screen::Screen() :Screen(L"", 800, 600) {
	// 현재 사용되지 않고 있음.
}

Screen::Screen(std::wstring title, int width, int height) {
	hInst_ = GetModuleHandle(NULL);
	FreeConsole(); // No console
	// Register win class
	WNDCLASSEX Wc;

	Wc.cbSize = sizeof(WNDCLASSEX);
	Wc.style = CS_HREDRAW | CS_VREDRAW;
	Wc.lpfnWndProc = WndProc;
	Wc.cbClsExtra = 0;
	Wc.cbWndExtra = 0;
	Wc.hInstance = hInst_;
	Wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wc.lpszMenuName = NULL;
	Wc.lpszClassName = L"MyWin";
	Wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&Wc);

	hWnd_ = CreateWindowExW(WS_EX_TOPMOST, L"MyWin", (WCHAR*)title.c_str(),
		WS_OVERLAPPED |
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // 종료 최소화 최대화 아이콘
		WS_THICKFRAME,  // resize가 가능하게
		0, 0, width, height, // x, y, width, height
		NULL, NULL, hInst_, NULL);  // Parent, Menu, instance handle, lpParam
	if (!hWnd_) throw 0;

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_); 
	SetFocus(hWnd_);
	hDC_ = GetDC(hWnd_);
	graphics_ = new Graphics(hDC_);
	invalidate();
}


// run 함수는 수정하면 위험함.
void Screen::eventLoop() {
	HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));
	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void Screen::initialize() {
	// 아직은 할 일이 없음.
	JButton* jb1 = new JButton("사각형");
	addButton(jb1); jb1->setBounds(10, 10, 100, 25); //여긴 수정 안해도 될 것 같음
	JButton* jb2 = new JButton("타원");
	addButton(jb2); jb2->setBounds(120, 10, 100, 25);
}

bool Screen::eventHandler(MyEvent e)
{
	// Stage 4. 여기에 버튼 찾는 기능을 추가
	

	// TODO: 여기에 구현 코드 추가.
	if (e.isLButtonDownEvent()) {
		// 여기서는 버튼을 클릭한 것인지 확인하고(findButton)
		// 거기에 맞는 액션을 하면 된다.
		// 버튼을 누른것이라면 누른 버튼을 기억시켜야한다.(멤버 변수 사용)   //tempBtn을 사용
		// 아니라면 이전처럼 위치만 기억시킨다.
		tempBtn = findButton(e);
		
		if (tempBtn == nullptr) {
			onLButtonDown(e);
		}
	}
	else if (e.isLButtonUpEvent()) {
		// 여기서도 버튼을 클릭한 것인지 확인하고(findButton)
		// 거기에 맞는 액션을 하면 된다.
		// 직전에 눌렀던 버튼이라면 (button down 시에 기억) 버튼의 onclick을 호출.
		// 버튼을 눌렀는데 뗄 때는 그 버튼 위치가 아닌 경우,
		// 뗄 때는 버튼인데 누른 버튼과 다르거나 버튼을 누른 적이 없으면 아무 일도 안한다.
		JButton* jb = findButton(e);

		if (jb == nullptr && tempBtn == nullptr) {
			onLButtonUp(e);
		}
		else if(jb == tempBtn){
			tempBtn->onClick();
		}
		
		tempBtn = nullptr;
	}
	return false;
}

void Screen::repaint() {
	// 여기서 모든 버튼을 그려준다.
	for (int i = 0; i < numButtons; i++) {
		button_[i]->repaint();
	}

	// 도형을 그린다.
	for (int i = 0; i < numShape; i++) {
		myshape[i]->draw();
	}
}

void Screen::invalidate() {
	// 이 메소드를 부르면 화면을 다시 그리게 된다.
	InvalidateRect(hWnd_, nullptr, true);

	// 다시 말해서 화면이 지워진 다음 repaint함수가 다시 호출된다.
}


Graphics * Screen::getGraphics() {
	return graphics_;
}

void Screen::onLButtonDown(MyEvent e)
{
	startx = e.getX();
	starty = e.getY();
}


void Screen::onLButtonUp(MyEvent e)
{
	endx = e.getX();
	endy = e.getY(); 
	//myrect[numRect++] = new MyRect(startx, starty, endx, endy, graphics_);
	if (figType_ == 0) {
		rect = new MyRect(startx, starty, endx, endy, graphics_);
		myshape[numShape++] = rect;
	}
	else if (figType_ == 1) {
		oval = new MyOval(startx, starty, endx, endy, graphics_);
		myshape[numShape++] = oval;
	}
	invalidate();
}

void Screen::addButton(JButton* jb) {
	// 완성해야함.
	button_[numButtons++] = jb;
	jb->setParent(this);
}

JButton* Screen::findButton(MyEvent e) {
	// 완성해야함.
	for (int i = 0; i < numButtons; i++) {
		JButton* currentButton = button_[i];
		if (currentButton->areYouThere(e.getX(), e.getY())) {
			return currentButton;
		}
	}
	return nullptr;
}

void Screen::setFigType(JButton *jb) {
	// Stage 4에서는 필요 없다.
	if (jb->getActionString() == "사각형") {
		figType_ = 0;
	}
	else if (jb->getActionString() == "타원") {
		figType_ = 1;
	}
}