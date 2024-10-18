#include "./OGUI/OpenGUILib.h"
#include <stdexcept>

int main() {
    try {
        Window myWindow("My Win32 Window", 800, 600);

        // Create a TextObject
        TextObject* myText = new TextObject();
        myText->AddText("Hello, Arial!", 150, 100, 24, "Arial");
        myText->AddText("Hello, Autumn Flower!", 150, 130, 24, "Autumn Flowers");
        myText->ChangeFont("./Fonts/AutumnFlowers.otf", "Autumn Flowers");
        myWindow.SetTextObject(myText);

        // Create a Button
        Button* myButton = new Button(myWindow.GetHandle(), "Click Me", 50, 100, 100, 50);
        myButton->AddEvent("onclick", []() {
            MessageBoxA(nullptr, "Button was clicked!", "Notification", MB_OK | MB_ICONINFORMATION);
        });
        myWindow.AddButton(myButton);
        myButton->Show();

        // Create a TextBox
        TextBox* myTextBox = new TextBox(myWindow.GetHandle(), 50, 200, 200, 30);
        myTextBox->SetMaxCharacterLength(100);
        myTextBox->SetBackgroundColor(RGB(240, 240, 240));
        myTextBox->SetTextColor(RGB(255, 0, 0));
        myTextBox->Show();

        // Create a TextBox
        TextBox* myTextBox2 = new TextBox(myWindow.GetHandle(), 200, 50, 200, 30);
        myTextBox2->SetMaxCharacterLength(100);
        myTextBox2->SetBackgroundColor(RGB(240, 240, 240));
        myTextBox2->SetTextColor(RGB(255, 0, 0));
        myTextBox2->Show();

        myWindow.AddResizeEvent([&myWindow, myButton, myTextBox]() {
            int windowWidth = myWindow.GetWidth();
            int windowHeight = myWindow.GetHeight();
            myButton->SetPosition((windowWidth - myButton->GetWidth()) / 2, (windowHeight - myButton->GetHeight()) / 2);
            myTextBox->SetPosition(50, 200);
        });

        myWindow.Show();
    } catch (const std::runtime_error& e) {
        MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    return 0;
}
