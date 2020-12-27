#include "drawText.h"

#include <sstream>

void DrawInt(int value, int x, int y, int size, Color color)
{
    std::ostringstream stream;
    stream << value;
    DrawText(stream.str().c_str(), x, y, size, color);
}

void DrawFloat(float value, int x, int y, int size, Color color)
{
    std::ostringstream stream;
    stream << value;
    DrawText(stream.str().c_str(), x, y, size, color);
}
