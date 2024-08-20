#include "cppdraw.h"
#include <imgui.h>

ImU32 color_;
float thickness_;
float fontSize_;

void newFrame()
{
    color_ = 0xffffffff;
    thickness_ = 1.f;
    //fontName_ = "";
    fontSize_ = 18;
}

clr RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (a << 24) | (b << 16) | (g << 8) | r;
}

void color(clr c)
{
    color_ = c;
}

void thickness(float th)
{
    thickness_ = th;
}

void font(ZStringView name, float fontSize)
{
    fontSize_ = fontSize;
}

void line(float x1, float y1, float x2, float y2)
{
    ImGui::GetWindowDrawList()->AddLine({ x1, y1 }, { x2, y2 }, color_, thickness_);
}