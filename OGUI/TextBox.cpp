#include "TextBox.h"
#include <stdexcept>

TextBox::TextBox(HWND parent, int x, int y, int width, int height)
    : maxCharacterLength(100), backgroundColor(RGB(255, 255, 255)), textColor(RGB(0, 0, 0)) {

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
        x, y, width, height,
        parent,
        nullptr,
        nullptr,
        nullptr
    );

    if (!hwnd) {
        throw std::runtime_error("Failed to create TextBox.");
    }

    SendMessage(hwnd, EM_SETBKGNDCOLOR, 0, backgroundColor);
    SendMessage(hwnd, EMR_SETTEXTCOLOR, 0, textColor);
}

void TextBox::SetPosition(int x, int y) {
    SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void TextBox::SetMaxCharacterLength(int length) {
    maxCharacterLength = length;
    SendMessage(hwnd, EM_SETLIMITTEXT, maxCharacterLength, 0); // Limit character input
}

void TextBox::SetBackgroundColor(COLORREF color) {
    backgroundColor = color;
    SendMessage(hwnd, EM_SETBKGNDCOLOR, 0, backgroundColor);
}

void TextBox::SetTextColor(COLORREF color) {
    textColor = color;
    SendMessage(hwnd, EMR_SETTEXTCOLOR, 0, textColor);
}

void TextBox::Show() {
    ShowWindow(hwnd, SW_SHOW);
}
