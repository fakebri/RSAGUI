#include "Util.h"

wchar_t* GetEditText(HWND hWnd) {
    // 处理按钮1的点击事件
    int textLength = GetWindowTextLength(hWnd);
    wchar_t* buffer = new wchar_t[textLength + 1];
    GetWindowText(hWnd, buffer, textLength + 1);

    return buffer;
}

std::vector<int> extractNumbers(const std::wstring& input) {
    std::vector<int> numbers;
    std::wregex pattern(L"\\{((\\d+)(,\\s*\\d+)*)\\}");
    std::wsmatch matches;

    if (std::regex_search(input, matches, pattern) && matches.size() >= 2) {
        std::wstring numbersStr = matches[1];
        std::wistringstream iss(numbersStr);
        int num;
        while (iss >> num) {
            numbers.push_back(num);
            if (iss.peek() == L',') {
                iss.ignore();
            }
        }
    }

    return numbers;
}