#include "Window.h"
#include <stdexcept>

Window::Window(const std::string& name, int width, int height) 
    : textObject(nullptr), resizeCallback(nullptr) {
    
    // Register the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "MyWindowClass";

    if (!RegisterClass(&wc)) {
        throw std::runtime_error("Failed to register window class.");
    }

    // Create the window
    hwnd = CreateWindowEx(
        0,
        "MyWindowClass",
        name.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr,
        nullptr,
        wc.hInstance,
        this // Pass this pointer to the window
    );

    if (!hwnd) {
        throw std::runtime_error("Failed to create window.");
    }
}

HWND Window::GetHandle() const {
    return hwnd;
}

void Window::Show() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    
    // Message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::SetTextObject(TextObject* textObject) {
    this->textObject = textObject;
}

void Window::AddButton(Button* button) {
    buttons.push_back(button);
}

int Window::GetWidth() const {
    RECT rect;
    GetClientRect(hwnd, &rect);
    return rect.right - rect.left;
}

int Window::GetHeight() const {
    RECT rect;
    GetClientRect(hwnd, &rect);
    return rect.bottom - rect.top;
}

void Window::AddResizeEvent(std::function<void()> callback) {
    resizeCallback = callback;
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static Window* window = nullptr;

    if (uMsg == WM_NCCREATE) {
        window = static_cast<Window*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        return TRUE;
    }

    window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            window->OnPaint(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_COMMAND: {
            // Check if a button was clicked
            for (auto button : window->buttons) {
                if (button->GetHandle() == (HWND)lParam) {
                    button->TriggerEvent("onclick");
                }
            }
            return 0;
        }
        case WM_SIZE: {
            // Re-center buttons on resize
            if (window->resizeCallback) {
                window->resizeCallback();
            }
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void Window::OnPaint(HDC hdc) {
    // Clear the background
    RECT rect;
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
    
    // Draw text object
    if (textObject) {
        textObject->Draw(hdc);
    }
}
