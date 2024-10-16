#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <string>
#include <windows.h>

class TextObject {
public:
    TextObject(const std::string& text, int x, int y, int fontSize, const std::string& fontName);
    TextObject(const std::string& text, int x, int y, int fontSize, const std::string& ttfPath, bool isTTF);
    void Draw(HDC hdc) const;
    ~TextObject(); // Destructor declaration

private:
    std::string text;
    int x;
    int y;
    int fontSize;
    HFONT hFont;
    void LoadOTFFont(const std::string& ttfPath);
};

#endif // TEXTOBJECT_H
