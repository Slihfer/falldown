#pragma once

#include <string>
#include <functional>

#include <raylib.h>

class Button
{
public:
    Rectangle shape;
    std::string label;
    int fontSize;
    std::function<void()> selectAction;
    bool selected;

public:
    Button(
        Rectangle shape,
        const std::string& label,
        int fontSize,
        const std::function<void()>& selectAction,
        bool selected = false);

public:
    void update();
    void draw();
}