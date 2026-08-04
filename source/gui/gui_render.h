#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <cstdio>
#include <cstdarg>
#include <cmath>
#include <cstring>

#pragma comment(lib, "opengl32.lib")

namespace Render
{
    inline HFONT  g_hFont = nullptr;
    inline GLuint g_fontBase = 0;
    inline bool   g_fontReady = false;

    inline void InitFont(int size = 14)
    {
        if (g_fontReady) return;
        HDC hdc = wglGetCurrentDC();
        if (!hdc) return;

        g_fontBase = glGenLists(256);
        if (!g_fontBase) return;

        g_hFont = CreateFontA(-size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");

        if (!g_hFont) {
            glDeleteLists(g_fontBase, 256);
            g_fontBase = 0;
            return;
        }

        HFONT old = (HFONT)SelectObject(hdc, g_hFont);
        if (!wglUseFontBitmapsA(hdc, 0, 256, g_fontBase)) {
            SelectObject(hdc, old);
            DeleteObject(g_hFont);
            glDeleteLists(g_fontBase, 256);
            g_hFont = nullptr;
            g_fontBase = 0;
            return;
        }
        SelectObject(hdc, old);

        g_fontReady = true;
    }

    inline void Shutdown()
    {
        if (g_fontReady) {
            glDeleteLists(g_fontBase, 256);
            DeleteObject(g_hFont);
            g_fontBase = 0; g_hFont = nullptr; g_fontReady = false;
        }
    }

    inline void RectFilled(float x, float y, float w, float h,
        float r, float g, float b, float a = 1.f)
    {
        glColor4f(r, g, b, a);
        glBegin(GL_QUADS);
        glVertex2f(x, y); glVertex2f(x + w, y);
        glVertex2f(x + w, y + h); glVertex2f(x, y + h);
        glEnd();
    }

    inline void RectOutline(float x, float y, float w, float h,
        float r, float g, float b, float a = 1.f)
    {
        glColor4f(r, g, b, a);
        glLineWidth(1.f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y); glVertex2f(x + w, y);
        glVertex2f(x + w, y + h); glVertex2f(x, y + h);
        glEnd();
    }

    inline void Text(float x, float y, float r, float g, float b, float a,
        const char* fmt, ...)
    {
        if (!g_fontReady || !fmt) return;
        char buf[256];
        va_list va; va_start(va, fmt);
        vsnprintf(buf, sizeof(buf), fmt, va);
        va_end(va);
        int len = (int)strlen(buf);
        if (len <= 0) return;
        glColor4f(r, g, b, a);
        glRasterPos2f(x, y);
        glPushAttrib(GL_LIST_BIT);
        glListBase(g_fontBase);
        glCallLists(len, GL_UNSIGNED_BYTE, (const GLubyte*)buf);
        glPopAttrib();
    }

    inline float TextWidth(const char* str, float charW = 8.f)
    {
        return str ? (float)strlen(str) * charW : 0.f;
    }

    inline void Begin2D(int w, int h)
    {
        if (!g_fontReady) InitFont();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
        glOrtho(0, w, h, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
        glDisable(GL_DEPTH_TEST); glDisable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    inline void End2D()
    {
        glMatrixMode(GL_PROJECTION); glPopMatrix();
        glMatrixMode(GL_MODELVIEW); glPopMatrix();
        glPopAttrib();
    }

    inline void DrawCursor(float x, float y)
    {
        glColor4f(1, 1, 1, 1);
        glBegin(GL_TRIANGLES);
        glVertex2f(x, y); glVertex2f(x, y + 16); glVertex2f(x + 10, y + 12);
        glEnd();
        glColor4f(0, 0, 0, 1);
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y); glVertex2f(x, y + 16); glVertex2f(x + 10, y + 12);
        glEnd();
    }
}