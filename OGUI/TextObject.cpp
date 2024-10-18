#include "TextObject.h"
#include <iostream>

TextObject::TextObject() {}

void TextObject::AddText(const std::string& text, int x, int y, int fontSize, const std::string& fontName) {
    TextEntry entry = {text, x, y, fontSize, nullptr};

    // Create the font for the entry
    if (fontName == "Arial") {
        entry.hFont = CreateFont(
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
            "Arial"
        );
    } else {
        CreateFontForEntry(entry, fontName); // For custom fonts
    }

    if (entry.hFont == nullptr) {
        throw std::runtime_error("Failed to create font for: " + text);
    }

    textEntries.push_back(entry);
}

void TextObject::ChangeFont(const std::string& fontPath, const std::string& fontName) {
    // Register the font resource
    if (AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, 0) == 0) {
        throw std::runtime_error("Failed to load OTF font.");
    }

    for (auto& entry : textEntries) {
        if (entry.hFont) {
            DeleteObject(entry.hFont); // Clean up existing font
        }
        CreateFontForEntry(entry, fontName); // Create new font
    }
}

void TextObject::CreateFontForEntry(TextEntry& entry, const std::string& fontName) {
    entry.hFont = CreateFont(
        entry.fontSize,
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
        fontName.c_str()
    );

    if (entry.hFont == nullptr) {
        std::cerr << "Failed to create font: " << fontName << std::endl;
    }
}

void TextObject::Draw(HDC hdc) const {
    for (const auto& entry : textEntries) {
        if (entry.hFont) {
            HFONT oldFont = (HFONT)SelectObject(hdc, entry.hFont);
            SetTextColor(hdc, RGB(0, 0, 0)); // Black color
            TextOut(hdc, entry.x, entry.y, entry.text.c_str(), entry.text.length());
            SelectObject(hdc, oldFont);
        } else {
            MessageBoxA(nullptr, "Font handle is null!", "Error", MB_OK | MB_ICONERROR);
        }
    }
}

TextObject::~TextObject() {
    for (const auto& entry : textEntries) {
        DeleteObject(entry.hFont);
    }
}
