#pragma once
#include <Windows.h>

namespace Input
{
    struct State
    {
        int  mouseX = 0;
        int  mouseY = 0;
        bool lmbDown = false;
        bool lmbClick = false;
    };

    inline State g_State;
    inline bool  g_ClickPending = false;

    inline void ProcessMessage(HWND, UINT msg, WPARAM, LPARAM)
    {
        switch (msg)
        {
        case WM_LBUTTONDOWN:
            g_State.lmbDown = true;
            g_ClickPending = true;
            break;
        case WM_LBUTTONUP:
            g_State.lmbDown = false;
            break;
        }
    }

    inline bool IsHovered(float x, float y, float w, float h)
    {
        return g_State.mouseX >= (int)x && g_State.mouseX <= (int)(x + w) &&
            g_State.mouseY >= (int)y && g_State.mouseY <= (int)(y + h);
    }

    inline bool IsClicked(float x, float y, float w, float h)
    {
        return g_State.lmbClick && IsHovered(x, y, w, h);
    }

    inline void NewFrame()
    {
        g_State.lmbClick = g_ClickPending;
        g_ClickPending = false;
    }
}