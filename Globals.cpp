
#include "Screen.h"
// 전역함수로는 윈도 메시지 처리 함수가 있다.
LRESULT CALLBACK WndProc(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_SIZE:
		if (Screen::mainScreen != nullptr)
			Screen::mainScreen->eventHandler(MyEvent(Msg, wParam, lParam));
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Hw, &ps);

		// 그리기 코드는 이걸로 끝!
		if (Screen::mainScreen != nullptr)
			Screen::mainScreen->repaint();

		EndPaint(Hw, &ps);  // BeginPaint의 짝이 된다

	}
	default: return DefWindowProc(Hw, Msg, wParam, lParam);
	}
	return DefWindowProc(Hw, Msg, wParam, lParam);
}

int debugCount = 0;
// 디버깅 용 전역 함수
void debugPrint(const char* s, int x) {
	char buf[80];
	sprintf_s(buf, "%d: %s %d\n", debugCount++, s, x);
	OutputDebugStringA(buf);
}
void debugPrint(int x, int y) {
	char buf[80];
	sprintf_s(buf, "%d: <%d, %d>\n", debugCount++, x, y);
	OutputDebugStringA(buf);
}
void debugPrint(const char* s) {
	char buf[80];
	sprintf_s(buf, "%d: %s\n", debugCount++, s);
	OutputDebugStringA(buf);
}

void debugPrint(const std::string s) {
	char buf[80];
	sprintf_s(buf, "%d: %s\n", debugCount++, s.c_str());
	OutputDebugStringA(buf);
}