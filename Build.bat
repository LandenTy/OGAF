@echo off
cd C:\Users\Landen.Barker\Desktop\OGUI Framework\Framework
g++ -o MyApp main.cpp ./OGUI/Window.cpp ./OGUI/TextObject.cpp ./OGUI/Button.cpp ./OGUI/TextBox.cpp -lgdi32 -mwindows
pause
