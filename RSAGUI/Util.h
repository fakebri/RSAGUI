#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

wchar_t* GetEditText(HWND hWnd);
std::vector<int> extractNumbers(const std::wstring& input);