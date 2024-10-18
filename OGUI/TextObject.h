#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <string>
#include <windows.h>
#include <vector>
#include <stdexcept>

class TextObject {
public:
    TextObject();
    void AddText(const std::string& text, int x, int y, int fontSize, const std::string& fontName);
    void ChangeFont(const std::string& fontPath, const std::string& fontName);
    void Draw(HDC hdc) const;
    ~TextObject();

private:
    struct TextEntry {
        std::string text;
        int x;
        int y;
        int fontSize;
        HFONT hFont;
    };

    std::vector<TextEntry> textEntries;

    void CreateFontForEntry(TextEntry& entry, const std::string& fontName);
};

#endif // TEXTOBJECT_H
