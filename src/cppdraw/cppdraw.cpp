#include "cppdraw.h"
#include <imgui.h>
#include <ctime>

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

void rect(float x1, float y1, float x2, float y2)
{
    ImGui::GetWindowDrawList()->AddRect({ x1, y1 }, { x2, y2 }, color_, 0, 0, thickness_);
}

void fillRect(float x1, float y1, float x2, float y2)
{
    ImGui::GetWindowDrawList()->AddRectFilled({ x1, y1 }, { x2, y2 }, color_);
}

void circle(float x1, float y1, float r)
{
    ImGui::GetWindowDrawList()->AddCircle({ x1, y1 }, r, color_, 0, thickness_);
}

void fillCircle(float x1, float y1, float r)
{
    ImGui::GetWindowDrawList()->AddCircleFilled({ x1, y1 }, r, color_, 0);
}

void fillTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    ImGui::GetWindowDrawList()->AddTriangleFilled({ x1, y1 }, { x2, y2 }, { x3, y3 }, color_);
}

void text(float x, float y, ZStringView str)
{
    ImGui::GetWindowDrawList()->AddText(nullptr, fontSize_, { x, y }, color_, str.c_str());
}

vec2 screenSize()
{
    return { ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y };
}

float time()
{
    return (float)ImGui::GetTime();
}

DateTime dateTime()
{
    time_t tt = time(0);
    tm* now = localtime(&tt);
    return { now->tm_hour, now->tm_min, now->tm_sec, now->tm_mday, now->tm_mon, now->tm_year };
}

bool mouseDown(int button)
{
    return ImGui::IsMouseDown(button);
}

vec2 mousePos()
{
    return { ImGui::GetMousePos().x, ImGui::GetMousePos().y };
}

bool keyDown(int key)
{
    return ImGui::IsKeyDown(ImGuiKey(key));
}