#pragma once
#include <stddef.h>
#include <cstring>

struct ZStringView {
    ZStringView()
        : str_(), size_()
    {}
    ZStringView(const char* s)
        : str_(s), size_(std::strlen(s))
    {}
    template <class T>
    ZStringView(const T& s)
        : str_(s.c_str()), size_(s.size())
    {}
    size_t size() const { return size_; }
    const char* c_str() const { return str_; }
    const char* begin() const { return c_str(); }
    const char* end() const { return begin() + size();}

private:
    const char* str_;
    size_t size_;
};

using ucolor = unsigned;

struct vec2 {
    float x, y;

    vec2() : x(), y() {}
    vec2(float x, float y) : x(x), y(y) {}
    vec2(const vec2& v) : x(v.x), y(v.y) {}
    vec2 operator+ (vec2 v) const { return { x+v.x, y+v.y }; }
    vec2 operator- (vec2 v) const { return { x-v.x, y-v.y }; }
    vec2 operator* (float f) const { return { f*x, f*y }; }
    friend vec2 operator* (float f, vec2 v) { return v*f; }
    vec2 operator/ (float f) const { return { x/f, y/f }; }
    vec2& operator+= (vec2 v) { *this = *this + v; return *this; }
    vec2& operator-= (vec2 v) { *this = *this - v; return *this; }
    vec2& operator*= (float f) { *this = *this * f; return *this; }
    vec2& operator/= (float f) { *this = *this / f; return *this; }
    friend float dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
    //friend float norm(vec2 a) { return std::sqrt(dot(a, a)); }
    friend float cross(vec2 a, vec2 b) { return a.x*b.y - a.y*b.x; }
};

struct DateTime {
    int h, m, s;
    int day, month, year;
};

ucolor RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);

//rendering

void color(ucolor c);

void font(ZStringView name, float fontSize);

void thickness(float th);

void line(float x1, float y1, float x2, float y2);

void rectangle(float x1, float y1, float x2, float y2);

void circle(float x1, float y1, float r);

void text(float x, float y, ZStringView text);

vec2 textExtents(ZStringView text);

void fillRect(float x1, float y1, float x2, float y2);

void fillRectWH(float x1, float y1, float w, float h);

void fillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

void fillQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

void fillCircle(float x1, float y1, float r);

vec2 screenSize();

void screenSize(ZStringView title, float w, float h);

ZStringView title();

//user interaction

float time();

float timeDelta();

DateTime dateTime();

bool mouseDown(int button = 0);

vec2 mousePos();

vec2 mouseDelta();

bool keyPressed(int key); //like ImGuiKey_A | ImGuiMod_Ctrl

void playSound(ZStringView path);

//

void newFrame();

extern void draw();
