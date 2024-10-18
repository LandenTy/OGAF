#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <windows.h>
#include <string>
#include <stdexcept>
#include <functional>
#include "richedit.h"

class TextBox {
public:
    TextBox(HWND parent, int x, int y, int width, int height);
    void SetPosition(int x, int y);
    void SetMaxCharacterLength(int length);
    void SetBackgroundColor(COLORREF color);
    void SetTextColor(COLORREF color);
    void Show();
    
private:
    HWND hwnd; // Handle for the TextBox
    int maxCharacterLength;
    COLORREF backgroundColor;
    COLORREF textColor;
};

#endif // TEXTBOX_H
