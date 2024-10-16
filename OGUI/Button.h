#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <windows.h>
#include <functional>
#include <map>

class Button {
public:
    Button(HWND parent, const std::string& text, int x, int y, int width, int height);
    
    void SetPosition(int x, int y);
    void SetText(const std::string& text);
    void Show();
    void SetBackgroundColor(COLORREF color); // New method to set background color
    COLORREF GetBackgroundColor() const; // New method to get background color

    HWND GetHandle() const { return hwnd; }

    // New methods to get button dimensions
    int GetWidth() const;
    int GetHeight() const;

    // Event handling
    void AddEvent(const std::string& eventName, std::function<void()> callback);
    void TriggerEvent(const std::string& eventName);

private:
    HWND hwnd; // Handle for the Win32 button
    std::map<std::string, std::function<void()>> events; // Map of events
    COLORREF backgroundColor; // Background color
};

#endif // BUTTON_H
