#ifndef COLOREDTEXT_H
#define COLOREDTEXT_H
#include <list>


class ColoredText{

    std::pmr::list<char> chars;
    std::pmr::list<int> colors;

public:
    ColoredText();
    ColoredText(const char* text, const int* color);
};

class TextColor{

    std::byte color;

public:
    TextColor(int foreground, int background);

    int Get();
};

enum Color {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_CYAN,
    DARK_RED,
    DARK_MAGENTA,
    DARK_YELLOW,
    DARK_WHITE,
    GRAY,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    YELLOW,
    WHITE
};


#endif //COLOREDTEXT_H
