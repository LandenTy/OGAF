# OGAF Setup Instructions

OGAF is a lightweight Win32 application framework that makes it easy to create user interfaces. Follow these steps to set it up in your project.

## 1. Clone the Repository

Open your command line interface (CLI) and run the following command to clone the OGAF repository into your project directory:

```bash
git clone https://github.com/LandenTy/OGAF.git [Project_Dir]\OGAF
```

## 2. Navigate to the OGAF Directory

Change your directory to the newly created OGAF folder:

```bash
cd [Project_Dir]\OGAF
```

## 3. Include OGAF in Your Project

Add the OGAF library to your project’s dependencies according to your development environment's guidelines.

```cpp
#include "OGUI/OpenGUILib.h>
```

## 5. Copy the Example Application

```cpp
#include "OGUI/OpenGUILib.h"
#include <stdexcept>

int main() {
    try {
        Window myWindow("My Win32 Window", 800, 600);
        
        // Create a TextObject using an OTF font
        TextObject* myText = new TextObject("Hello, World!", 100, 100, 24, "./Fonts/AutumnFlowers.otf", true);
        myWindow.SetTextObject(myText);

        // Create a Button using the Button class
        Button* myButton = new Button(myWindow.GetHandle(), "Click Me", 50, 100, 100, 50);
        
        // Add an event handler directly in main
        myButton->AddEvent("onclick", []() {
            MessageBoxA(nullptr, "Button was clicked!", "Notification", MB_OK | MB_ICONINFORMATION);
        });

        myWindow.AddButton(myButton); // Add the button to the window
        myButton->Show();

        // Center the button initially
        myWindow.AddResizeEvent([&myWindow, myButton]() {
            int windowWidth = myWindow.GetWidth();
            int windowHeight = myWindow.GetHeight();
            int buttonWidth = myButton->GetWidth();
            int buttonHeight = myButton->GetHeight();
            myButton->SetPosition((windowWidth - buttonWidth) / 2, (windowHeight - buttonHeight) / 2);
        });

        myWindow.Show();
    } catch (const std::runtime_error& e) {
        MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    return 0;
}
```

## 6. Start Building Your Application

You can now start using OGAF in your project! Refer to the documentation for examples on how to create windows, buttons, and other UI elements.
