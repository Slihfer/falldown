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
    int index;
    bool selected;

public:
    Button(
        Rectangle shape,
        const std::string& label,
        int fontSize,
        const std::function<void()>& selectAction);

public:
    void update();
    void draw();
};