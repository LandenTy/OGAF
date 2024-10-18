#include "Button.h"
#include <stdexcept>

Button::Button(HWND parent, const std::string& text, int x, int y, int width, int height) {
    hwnd = CreateWindow(
        "BUTTON",  // Predefined class; Unicode assumed 
        text.c_str(), // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        x,         // x position 
        y,         // y position 
        width,     // Button width
        height,    // Button height 
        parent,    // Parent window
        nullptr,   // No menu
        nullptr,   // Handle to the instance
        nullptr    // Pointer not needed
    );

    if (!hwnd) {
        throw std::runtime_error("Failed to create button.");
    }
}

void Button::SetPosition(int x, int y) {
    SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Button::SetText(const std::string& text) {
    SetWindowText(hwnd, text.c_str());
}

void Button::Show() {
    ShowWindow(hwnd, SW_SHOW);
}

int Button::GetWidth() const {
    RECT rect;
    GetClientRect(hwnd, &rect);
    return rect.right - rect.left;
}

int Button::GetHeight() const {
    RECT rect;
    GetClientRect(hwnd, &rect);
    return rect.bottom - rect.top;
}

void Button::AddEvent(const std::string& eventName, std::function<void()> callback) {
    events[eventName] = callback;
}

void Button::TriggerEvent(const std::string& eventName) {
    if (events.find(eventName) != events.end()) {
        events[eventName](); // Call the event callback
    }
}
