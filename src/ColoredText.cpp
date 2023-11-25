#include "ColoredText.h"

#include <list>

ColoredText::ColoredText() = default;

ColoredText::ColoredText(const char* text, const int* color) {
     // chars = &text[1];
}


TextColor::TextColor(const int foreground, const int background) {
     color = static_cast<std::byte>(background) << 4 | static_cast<std::byte>(foreground);
}

int TextColor::Get() {
     return static_cast<int>(color);
}
