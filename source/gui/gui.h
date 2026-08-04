#pragma once
#include <Windows.h>
#include "gui_render.h"
#include "gui_input.h"

namespace GUI
{
    extern bool g_IsOpen;
    extern HWND g_hWnd;

    void Init(HWND hWnd);
    void Render(int screenW, int screenH);
    void Shutdown();

    void Checkbox(const char* label, bool* val);
    void ColorPicker3(const char* label, float col[4]);
}