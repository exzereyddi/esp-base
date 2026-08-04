#include "pch.h"
#include "gui/gui.h"
#include "visuals/esp.h"
#include "core/unload.h"

namespace GUI
{
    bool g_IsOpen = false;
    HWND g_hWnd = nullptr;

    static WNDPROC g_OldWndProc = nullptr;
    static bool  g_Dragging = false;
    static float g_DragX = 0, g_DragY = 0;
    static float g_WinX = 200, g_WinY = 200;
    static float g_WinW = 260, g_WinH = 290;
    static float g_CurY = 0;

    static const float PAD = 10.f;
    static const float TITLE_H = 28.f;
    static const float ITEM_H = 22.f;
    static const float GAP = 4.f;

    static LRESULT WINAPI WndProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
    {
        if (g_IsOpen) {
            Input::ProcessMessage(hw, msg, wp, lp);

            switch (msg) {
            case WM_MOUSEMOVE: case WM_LBUTTONDOWN: case WM_LBUTTONUP:
            case WM_RBUTTONDOWN: case WM_RBUTTONUP: case WM_MOUSEWHEEL:
            case WM_KEYDOWN: case WM_KEYUP: case WM_CHAR:
            case WM_XBUTTONDOWN: case WM_XBUTTONUP:
                return TRUE;

            case WM_INPUT:
                return TRUE;

            case WM_SETCURSOR:
                SetCursor(NULL);
                return TRUE;
            }
        }
        return CallWindowProcA(g_OldWndProc, hw, msg, wp, lp);
    }

    void Init(HWND hWnd)
    {
        g_hWnd = hWnd;
        g_OldWndProc = (WNDPROC)SetWindowLongPtrA(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
    }

    void Shutdown()
    {
        if (g_hWnd && g_OldWndProc) {
            SetWindowLongPtrA(g_hWnd, GWLP_WNDPROC, (LONG_PTR)g_OldWndProc);
            g_OldWndProc = nullptr;
        }
        Render::Shutdown();
    }

    static void NextLine() { g_CurY += ITEM_H + GAP; }

    void Checkbox(const char* label, bool* val)
    {
        float x = g_WinX + PAD;
        float y = g_CurY;
        float w = g_WinW - PAD * 2;
        float sz = 14.f;

        bool hov = Input::IsHovered(x, y, w, ITEM_H);
        if (Input::IsClicked(x, y, w, ITEM_H)) *val = !(*val);

        float by = y + (ITEM_H - sz) * 0.5f;
        Render::RectFilled(x, by, sz, sz, 0.14f, 0.16f, 0.22f, 1.f);
        Render::RectOutline(x, by, sz, sz, 0.3f, 0.35f, 0.5f, 0.6f);
        if (*val)
            Render::RectFilled(x + 3, by + 3, sz - 6, sz - 6, 0.26f, 0.6f, 1.f, 1.f);

        Render::Text(x + sz + 8, y + 15,
            hov ? 1.f : 0.88f, hov ? 1.f : 0.9f, hov ? 1.f : 0.94f, 1.f, label);
        NextLine();
    }

    void ColorPicker3(const char* label, float col[4])
    {
        float x = g_WinX + PAD;
        float y = g_CurY;
        float w = g_WinW - PAD * 2;
        float pvW = 40.f, pvH = 14.f;
        float pvX = x + w - pvW;
        float pvY = y + (ITEM_H - pvH) * 0.5f;

        Render::Text(x, y + 15, 0.88f, 0.9f, 0.94f, 1.f, label);
        Render::RectFilled(pvX, pvY, pvW, pvH, col[0], col[1], col[2], 1.f);
        Render::RectOutline(pvX, pvY, pvW, pvH, 0.3f, 0.35f, 0.5f, 0.7f);
        NextLine();
    }

    void Render(int screenW, int screenH)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1) g_IsOpen = !g_IsOpen;
        if (!g_IsOpen) return;

        ClipCursor(NULL);
        POINT pt; GetCursorPos(&pt); ScreenToClient(g_hWnd, &pt);
        Input::g_State.mouseX = pt.x;
        Input::g_State.mouseY = pt.y;

        Render::Begin2D(screenW, screenH);
        Input::NewFrame();

        float mx = (float)Input::g_State.mouseX;
        float my = (float)Input::g_State.mouseY;

        if (!g_Dragging && Input::IsClicked(g_WinX, g_WinY, g_WinW, TITLE_H)) {
            g_Dragging = true;
            g_DragX = mx - g_WinX;
            g_DragY = my - g_WinY;
        }
        if (g_Dragging) {
            if (Input::g_State.lmbDown) {
                g_WinX = mx - g_DragX;
                g_WinY = my - g_DragY;
            }
            else g_Dragging = false;
        }

        Render::RectFilled(g_WinX + 3, g_WinY + 3, g_WinW, g_WinH, 0, 0, 0, 0.4f);
        Render::RectFilled(g_WinX, g_WinY, g_WinW, g_WinH, 0.07f, 0.08f, 0.11f, 0.96f);
        Render::RectOutline(g_WinX, g_WinY, g_WinW, g_WinH, 0.2f, 0.25f, 0.4f, 0.7f);

        Render::RectFilled(g_WinX, g_WinY, g_WinW, TITLE_H, 0.09f, 0.1f, 0.14f, 1.f);
        Render::RectFilled(g_WinX, g_WinY + TITLE_H - 2, g_WinW, 2, 0.26f, 0.6f, 1.f, 1.f);
        float tw = Render::TextWidth("opsec", 8.f);
        Render::Text(g_WinX + (g_WinW - tw) * 0.5f, g_WinY + 19,
            0.85f, 0.9f, 1.f, 1.f, "opsec");

        g_CurY = g_WinY + TITLE_H + PAD;

        Checkbox("ESP Enabled", &ESPSettings::espEnabled);
        Checkbox("Box", &ESPSettings::espBox);
        Checkbox("Name", &ESPSettings::espName);
        Checkbox("Teammates", &ESPSettings::espTeammates);
        Checkbox("Visible Only", &ESPSettings::espVisibleOnly);
        ColorPicker3("Color CT", ESPSettings::espColorCT);
        ColorPicker3("Color T", ESPSettings::espColorT);

        float bx = g_WinX + PAD;
        float by = g_CurY;
        float bw = g_WinW - PAD * 2;
        float bh = 24.f;
        bool bHov = Input::IsHovered(bx, by, bw, bh);
        if (Input::IsClicked(bx, by, bw, bh)) Unload::Request();
        Render::RectFilled(bx, by, bw, bh,
            bHov ? 0.6f : 0.4f, bHov ? 0.15f : 0.1f, bHov ? 0.15f : 0.1f, 1.f);
        Render::RectOutline(bx, by, bw, bh, 0.5f, 0.2f, 0.2f, 0.8f);
        float uw = Render::TextWidth("UNLOAD", 8.f);
        Render::Text(bx + (bw - uw) * 0.5f, by + 16, 1.f, 0.9f, 0.9f, 1.f, "UNLOAD");


        Render::DrawCursor(mx, my);
        Render::End2D();
    }
}