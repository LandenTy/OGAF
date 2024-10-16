#include "TextObject.h"
#include <stdexcept>

TextObject::TextObject(const std::string& text, int x, int y, int fontSize, const std::string& fontName)
    : text(text), x(x), y(y), fontSize(fontSize), hFont(nullptr) {
    hFont = CreateFont(
        fontSize,           // Height of font
        0,                 // Width of font
        0,                 // Angle of escapement
        0,                 // Base-line angle
        FW_NORMAL,         // Font weight
        FALSE,             // Italic
        FALSE,             // Underline
        FALSE,             // Strikeout
        DEFAULT_CHARSET,   // Character set identifier
        OUT_DEFAULT_PRECIS,// Output precision
        CLIP_DEFAULT_PRECIS,// Clipping precision
        DEFAULT_QUALITY,   // Output quality
        DEFAULT_PITCH | FF_DONTCARE, // Pitch and family
        fontName.c_str()   // Font name
    );
}

TextObject::TextObject(const std::string& text, int x, int y, int fontSize, const std::string& fontPath, bool isOTF)
    : text(text), x(x), y(y), fontSize(fontSize), hFont(nullptr) {
    if (isOTF) {
        LoadOTFFont(fontPath);
    } else {
        hFont = CreateFont(
            fontSize,
            0,
            0,
            0,
            FW_NORMAL,
            FALSE,
            FALSE,
            FALSE,
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            fontPath.c_str() // Treat as font name if not OTF
        );
    }
}

void TextObject::LoadOTFFont(const std::string& fontPath) {
    // Load the font resource
    if (AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, 0) == 0) {
        throw std::runtime_error("Failed to load OTF font.");
    }

    // Create the font using the actual name of the font
    hFont = CreateFont(
        fontSize,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        "Your Font Name Here" // Replace this with the actual font name
    );
}

void TextObject::Draw(HDC hdc) const {
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
    
    SetTextColor(hdc, RGB(0, 0, 0)); // Black color

    TextOut(hdc, x, y, text.c_str(), text.length());

    SelectObject(hdc, oldFont);
}

TextObject::~TextObject() {
    DeleteObject(hFont);
}
