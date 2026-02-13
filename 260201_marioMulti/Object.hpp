#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <cmath>

class Object {
public:
    float x, y;
    float width, height;
    float vert_speed;
    float horiz_speed;
    bool is_fly;
    char ctype;

    Object(float xpos = 0, float ypos = 0, float owidth = 0, float oheight = 0, char type = '-')
        : x(xpos), y(ypos), width(owidth), height(oheight), vert_speed(0), horiz_speed(0.2f), is_fly(false), ctype(type) {}

    void setPosition(float xpos, float ypos) {
        x = xpos;
        y = ypos;
    }
};

#endif