#include "Graphics.h"
Graphics::Graphics(HDC hdc):hDC_(hdc) {
	// nothing
}

void Graphics::drawRect(int x, int y, int width, int height) {
	Rectangle(hDC_, x, y, x + width, y + height);
}

void Graphics::drawString(std::string s, int x, int y) {
	TextOutA(hDC_, x, y, s.c_str(), strlen(s.c_str()));
}

void Graphics::drawOval(int x, int y, int width, int height) {
	Ellipse(hDC_, x, y, x + width, y + height);
}
