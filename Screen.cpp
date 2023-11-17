#include "Screen.h"
#include "Etc.h"
#include "JButton.h"
#include <iostream>



Screen::Screen() :Screen(L"", 800, 600) {
	// ���� ������ �ʰ� ����.
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
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // ���� �ּ�ȭ �ִ�ȭ ������
		WS_THICKFRAME,  // resize�� �����ϰ�
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


// run �Լ��� �����ϸ� ������.
void Screen::eventLoop() {
	HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));
	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
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
	// ������ �� ���� ����.
	JButton* jb1 = new JButton("�簢��");
	addButton(jb1); jb1->setBounds(10, 10, 100, 25); //���� ���� ���ص� �� �� ����
	JButton* jb2 = new JButton("Ÿ��");
	addButton(jb2); jb2->setBounds(120, 10, 100, 25);
}

bool Screen::eventHandler(MyEvent e)
{
	// Stage 4. ���⿡ ��ư ã�� ����� �߰�
	

	// TODO: ���⿡ ���� �ڵ� �߰�.
	if (e.isLButtonDownEvent()) {
		// ���⼭�� ��ư�� Ŭ���� ������ Ȯ���ϰ�(findButton)
		// �ű⿡ �´� �׼��� �ϸ� �ȴ�.
		// ��ư�� �������̶�� ���� ��ư�� �����Ѿ��Ѵ�.(��� ���� ���)   //tempBtn�� ���
		// �ƴ϶�� ����ó�� ��ġ�� ����Ų��.
		tempBtn = findButton(e);
		
		if (tempBtn == nullptr) {
			onLButtonDown(e);
		}
	}
	else if (e.isLButtonUpEvent()) {
		// ���⼭�� ��ư�� Ŭ���� ������ Ȯ���ϰ�(findButton)
		// �ű⿡ �´� �׼��� �ϸ� �ȴ�.
		// ������ ������ ��ư�̶�� (button down �ÿ� ���) ��ư�� onclick�� ȣ��.
		// ��ư�� �����µ� �� ���� �� ��ư ��ġ�� �ƴ� ���,
		// �� ���� ��ư�ε� ���� ��ư�� �ٸ��ų� ��ư�� ���� ���� ������ �ƹ� �ϵ� ���Ѵ�.
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
	// ���⼭ ��� ��ư�� �׷��ش�.
	for (int i = 0; i < numButtons; i++) {
		button_[i]->repaint();
	}

	// ������ �׸���.
	for (int i = 0; i < numShape; i++) {
		myshape[i]->draw();
	}
}

void Screen::invalidate() {
	// �� �޼ҵ带 �θ��� ȭ���� �ٽ� �׸��� �ȴ�.
	InvalidateRect(hWnd_, nullptr, true);

	// �ٽ� ���ؼ� ȭ���� ������ ���� repaint�Լ��� �ٽ� ȣ��ȴ�.
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
	// �ϼ��ؾ���.
	button_[numButtons++] = jb;
	jb->setParent(this);
}

JButton* Screen::findButton(MyEvent e) {
	// �ϼ��ؾ���.
	for (int i = 0; i < numButtons; i++) {
		JButton* currentButton = button_[i];
		if (currentButton->areYouThere(e.getX(), e.getY())) {
			return currentButton;
		}
	}
	return nullptr;
}

void Screen::setFigType(JButton *jb) {
	// Stage 4������ �ʿ� ����.
	if (jb->getActionString() == "�簢��") {
		figType_ = 0;
	}
	else if (jb->getActionString() == "Ÿ��") {
		figType_ = 1;
	}
}