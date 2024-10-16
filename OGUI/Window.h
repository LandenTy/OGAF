#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <vector>
#include <windows.h>
#include "TextObject.h"
#include "Button.h"

class Window {
public:
    Window(const std::string& name, int width, int height);
    void Show();
    void SetTextObject(TextObject* textObject);
    HWND GetHandle() const;

    void AddButton(Button* button);
    
    // New methods for getting window dimensions
    int GetWidth() const;
    int GetHeight() const;

    // Method to handle window resize events
    void AddResizeEvent(std::function<void()> callback);

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void OnPaint(HDC hdc);
    void HandleResize();

    HWND hwnd;
    TextObject* textObject;
    std::vector<Button*> buttons; // Store buttons
    std::function<void()> resizeCallback; // Callback for resize events
};

#endif // WINDOW_H
