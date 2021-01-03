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
    std::function<void()> action;
    int index;
    bool selected;
    bool mouseOnly;

public:
    Button(
        Rectangle shape,
        const std::string& label,
        int fontSize,
        const std::function<void()>& action,
        bool mouseOnly = false);

public:
    void update();
    void draw();
};