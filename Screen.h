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
	// Window ���α׷����� ���� �⺻ �������̴�. �ǵ帮�� �ʴ´�.
	HINSTANCE hInst_;
	HWND hWnd_;	 // ���� �ڵ��� �����صд�.
	HDC hDC_;    // �� ������ �־�� �׸��� �׸� �� �ִ�.
	Graphics * graphics_ ;
public:
	static Screen* mainScreen;	// ���� ���� ��� static ���� �Ѵ�.

	Screen();
	Screen(std::wstring, int, int);
	virtual void eventLoop();

	Graphics * getGraphics() ;
	virtual bool eventHandler( MyEvent e);
	virtual void repaint();
	void invalidate();	// ������ ȭ���� �ٽ� �׷������ϴ� �������� �˸�.
	virtual void initialize() ;  // Must override
	void setFigType(JButton *);	
	
	// GUI �� ���� �Լ�
	void addButton(JButton*);
	JButton * findButton(MyEvent e);	// ��ư�� areYouThere �Լ��� �̿��ؼ� ã�� �Լ�

private:
	// GUI�� ���� ���� ����
	JButton* button_[100];
	int numButtons = 0;

	JButton* tempBtn = nullptr; //Ŭ�������� tempBtn�� �����ϰ� Ŭ���� ������� Ŭ���������� ��ư�� �����Ѱ� �ٸ����� �Ǵ��� �� ����� ����.
	// ������ ���� ���� ����
private:
	MyShape* myshape[100]; //������ü
	int numShape = 0; //�������� 
	MyRect* rect; //�ӽ� �簢�� ��ü
	MyOval* oval; //�ӽ� Ÿ�� ��ü
	// �ӽ� ����
	int startx, starty, endx, endy;
	int figType_ = 0;  //0�̸� �簢�� ����, 1�̸� Ÿ�� �������� ���.
public:
	void onLButtonDown(MyEvent e);
	void onLButtonUp(MyEvent e);
};