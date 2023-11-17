#pragma once
#include "Windows.h"

LRESULT CALLBACK WndProc(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam);
void debugPrint(const char* s, int x);
void debugPrint(int x, int y);
void debugPrint(const char* s);
void debugPrint(const std::string s);
