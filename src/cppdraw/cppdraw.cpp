#include "cppdraw.h"
#include <imgui.h>
#include <ctime>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#undef RGB

ImU32 color_;
float thickness_;
float fontSize_;
float lastTime_;
float time_;
vec2 lastMousePos_;
vec2 mousePos_;
vec2 screenSize_;
std::string title_;

void newFrame()
{
    color_ = 0xffffffff;
    thickness_ = 1.f;
    //fontName_ = "";
    title_ = "cppdraw";
    fontSize_ = 18;
    lastTime_ = time_;
    time_ = (float)ImGui::GetTime();
    lastMousePos_ = mousePos_;
    mousePos_ = { ImGui::GetMousePos().x, ImGui::GetMousePos().y };
    if (!screenSize_.x || !screenSize_.y)
        screenSize_ = { 800, 600 };
    else
        screenSize_ = { ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y };
}

//----------------------------------------------------------

ucolor RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (a << 24) | (b << 16) | (g << 8) | r;
}

void color(ucolor c)
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

void rectangle(float x1, float y1, float x2, float y2)
{
    ImGui::GetWindowDrawList()->AddRect({ x1, y1 }, { x2, y2 }, color_, 0, 0, thickness_);
}

void fillRect(float x1, float y1, float x2, float y2)
{
    ImGui::GetWindowDrawList()->AddRectFilled({ x1, y1 }, { x2, y2 }, color_);
}

void fillRectWH(float x1, float y1, float w, float h)
{
    fillRect(x1, y1, x1 + w, y1 + h);
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

void fillQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    fillTriangle(x1, y1, x2, y2, x3, y3);
    fillTriangle(x3, y3, x4, y4, x1, y1);
}

void text(float x, float y, ZStringView str)
{
    ImGui::GetWindowDrawList()->AddText(nullptr, fontSize_, { x, y }, color_, str.c_str());
}

vec2 textExtents(ZStringView str)
{
    auto sz = ImGui::CalcTextSize(str.c_str());
    float scale = fontSize_ / ImGui::GetFontSize();
    return { scale * sz.x, scale * sz.y };
}

vec2 screenSize()
{
    return screenSize_;
}

void screenSize(ZStringView title, float w, float h)
{
    title_.assign(title.c_str(), title.size());
    screenSize_ = { w, h };
}

ZStringView title()
{
    return title_;
}

float time()
{
    return time_;
}

float timeDelta()
{
    return time_ - lastTime_;
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
    return mousePos_;
}

vec2 mouseDelta()
{
    return mousePos_ - lastMousePos_;
}

bool keyPressed(int key)
{
    int mod = key & ImGuiMod_Mask_;
    if (!ImGui::IsKeyPressed(ImGuiKey(key & (~ImGuiMod_Mask_))))
        return false;
    return ImGui::GetIO().KeyMods == mod;
}

void playSound(ZStringView path)
{
    PlaySoundA(path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}
