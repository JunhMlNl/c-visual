
#include "Screen.h"
#include <iostream>
#include <exception>



// 클래스 변수(static)를 초기화한다.
Screen * Screen::mainScreen = new Screen(L"프로젝트2023", 1000, 800);

int main() {
	try {
		Screen::mainScreen->initialize();
		Screen::mainScreen->eventLoop();
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
}
