#include "pch.h"
#include "visuals/esp.h"
#include "gui/gui_render.h"

namespace ESPSettings {
    bool  espEnabled = false;
    bool  espBox = true;
    bool  espName = true;
    bool  espTeammates = false;
    bool  espVisibleOnly = false;
    float espColorCT[4] = { 0.30f, 0.60f, 1.00f, 1.f };
    float espColorT[4] = { 1.00f, 0.30f, 0.30f, 1.f };
}

static std::vector<ESPPlayerData> g_Players;
static uintptr_t g_hwMod = 0;

void ESP_AddPlayer(const ESPPlayerData& data)
{
    if (g_Players.size() > 128) g_Players.clear();
    g_Players.push_back(data);
}

void ESP_Reset()
{
    g_Players.clear();
    g_hwMod = 0;
}

static bool W2S(vec3 pos, vec2& out, float m[16], int w, int h)
{
    float c[4];
    c[0] = pos.x * m[0] + pos.y * m[4] + pos.z * m[8] + m[12];
    c[1] = pos.x * m[1] + pos.y * m[5] + pos.z * m[9] + m[13];
    c[2] = pos.x * m[2] + pos.y * m[6] + pos.z * m[10] + m[14];
    c[3] = pos.x * m[3] + pos.y * m[7] + pos.z * m[11] + m[15];
    if (c[3] < 0.1f) return false;
    out.x = (w * 0.5f * c[0] / c[3]) + w * 0.5f;
    out.y = -(h * 0.5f * c[1] / c[3]) + h * 0.5f;
    return true;
}

static bool IsVisible(vec3 from, vec3 to)
{
    if (!g_Offsets.pEngineFunc || !g_Offsets.pEngineFunc->PM_TraceLine)
        return true;
    float s[3] = { from.x, from.y, from.z };
    float e[3] = { to.x, to.y, to.z };
    __try {
        pmtrace_s* tr = g_Offsets.pEngineFunc->PM_TraceLine(s, e, 0, 2, -1);
        return tr && tr->fraction >= 0.95f;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return true; }
}

void DrawESP(int winW, int winH)
{
    if (!ESPSettings::espEnabled) { g_Players.clear(); return; }

    if (!g_hwMod) {
        g_hwMod = (uintptr_t)GetModuleHandleA("hw.dll");
        if (!g_hwMod) g_hwMod = (uintptr_t)GetModuleHandleA("engine.dll");
    }
    if (!g_hwMod) { g_Players.clear(); return; }

    float vm[16];
    __try { memcpy(vm, (void*)(g_hwMod + 0xEC9780), sizeof(vm)); }
    __except (EXCEPTION_EXECUTE_HANDLER) { g_Players.clear(); return; }

    for (auto& p : g_Players)
    {
        vec2 h2d, f2d;
        if (!W2S(p.head, h2d, vm, winW, winH)) continue;
        if (!W2S(p.feet, f2d, vm, winW, winH)) continue;

        float height = f2d.y - h2d.y;
        if (height < 10.f || height > 800.f) continue;

        if (ESPSettings::espVisibleOnly && g_Offsets.pmove) {
            vec3 eye = {
                g_Offsets.pmove->origin[0] + g_Offsets.pmove->view_ofs[0],
                g_Offsets.pmove->origin[1] + g_Offsets.pmove->view_ofs[1],
                g_Offsets.pmove->origin[2] + g_Offsets.pmove->view_ofs[2]
            };
            vec3 mid = {
                (p.head.x + p.feet.x) * 0.5f,
                (p.head.y + p.feet.y) * 0.5f,
                (p.head.z + p.feet.z) * 0.5f
            };
            if (!IsVisible(eye, mid)) continue;
        }

        float* col = (p.team == 2) ? ESPSettings::espColorCT : ESPSettings::espColorT;
        float width = height / 2.f;
        float x = h2d.x - width * 0.5f;
        float y = h2d.y;

        if (ESPSettings::espBox)
            Render::RectOutline(x, y, width, height, col[0], col[1], col[2], col[3]);

        if (ESPSettings::espName && p.name[0]) {
            float tw = Render::TextWidth(p.name, 8.f);
            Render::Text(x + width * 0.5f - tw * 0.5f, y - 4,
                1.f, 1.f, 1.f, 1.f, p.name);
        }
    }

    g_Players.clear();
}