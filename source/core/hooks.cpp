#include "pch.h"
#include "hooks.h"
#include "hook_manager.h"
#include "offsets.h"
#include "unload.h"
#include "gui/gui.h"
#include "gui/gui_render.h"
#include "visuals/esp.h"

static HMODULE g_hModule = nullptr;
volatile bool  g_ShouldUnload = false;

static HWND  g_GameHwnd = nullptr;
static bool  g_Initialized = false;
static bool  g_HooksInstalled = false;

static uintptr_t g_hwModule = 0;
static uintptr_t g_clientModule = 0;

typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC);
static wglSwapBuffers_t o_wglSwapBuffers = nullptr;
static BYTE  g_SwapBytes[5] = {};
static void* g_SwapAddr = nullptr;
static volatile bool g_InSwap = false;

typedef int(__cdecl* HUD_AddEntity_t)(int, struct cl_entity_s*, const char*);
static HUD_AddEntity_t o_HUD_AddEntity = nullptr;
static bool g_HudHooked = false;

typedef int(*GetPlayerInfo_t)(int, hud_player_info_t*);
static GetPlayerInfo_t g_GetPlayerInfo = nullptr;

static int __cdecl hkHUD_AddEntity(int type, cl_entity_s* ent, const char* model)
{
    if (g_ShouldUnload || !ent || !ent->player)
        return o_HUD_AddEntity ? o_HUD_AddEntity(type, ent, model) : 0;

    __try {
        if (ent->index >= 1 && ent->index <= 32) {
            int localIdx = g_Offsets.pmove ? g_Offsets.pmove->player_index + 1 : 0;
            if (ent->index != localIdx && g_clientModule) {
                char team = *(char*)(g_clientModule + 0x12F44C + ent->index * 0x74);
                int teamId = (team == 'C') ? 2 : (team == 'T' ? 1 : 0);

                int localTeam = 0;
                if (localIdx > 0) {
                    char lt = *(char*)(g_clientModule + 0x12F44C + localIdx * 0x74);
                    localTeam = (lt == 'C') ? 2 : (lt == 'T' ? 1 : 0);
                }

                bool isEnemy = (localTeam != teamId);
                if (ESPSettings::espEnabled &&
                    (isEnemy || ESPSettings::espTeammates))
                {
                    ESPPlayerData data = {};
                    data.head = { ent->origin[0], ent->origin[1], ent->origin[2] + 28.0f };
                    data.feet = { ent->origin[0], ent->origin[1], ent->origin[2] - 35.0f };
                    data.team = teamId;
                    data.index = ent->index;

                    if (g_GetPlayerInfo) {
                        hud_player_info_t info = {};
                        __try {
                            g_GetPlayerInfo(ent->index, &info);
                            if (info.name && info.name[0])
                                strncpy(data.name, info.name, 31);
                        }
                        __except (EXCEPTION_EXECUTE_HANDLER) {}
                    }
                    if (!data.name[0])
                        snprintf(data.name, sizeof(data.name), "Player_%d", ent->index);

                    ESP_AddPlayer(data);
                }
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {}

    return o_HUD_AddEntity ? o_HUD_AddEntity(type, ent, model) : 0;
}

static void HookHUD_AddEntity()
{
    if (g_HudHooked) return;
    g_hwModule = (uintptr_t)GetModuleHandleA("hw.dll");
    if (!g_hwModule) g_hwModule = (uintptr_t)GetModuleHandleA("engine.dll");
    g_clientModule = (uintptr_t)GetModuleHandleA("client.dll");
    if (!g_hwModule || !g_clientModule) return;

    if (g_Offsets.pEngineFunc)
        g_GetPlayerInfo = (GetPlayerInfo_t)g_Offsets.pEngineFunc->pfnGetPlayerInfo;

    if (HookManager::HookIAT(g_hwModule + 0x122EDB0,
        (void*)hkHUD_AddEntity, (void**)&o_HUD_AddEntity))
        g_HudHooked = true;
}

static void UnhookHUD_AddEntity()
{
    if (!g_HudHooked || !o_HUD_AddEntity || !g_hwModule) return;
    HookManager::UnhookIAT(g_hwModule + 0x122EDB0, (void*)o_HUD_AddEntity);
    g_HudHooked = false;
    o_HUD_AddEntity = nullptr;
}

static void InstallGameHooks()
{
    if (g_HooksInstalled) return;
    HookHUD_AddEntity();
    g_HooksInstalled = true;
}

static void RemoveGameHooks()
{
    UnhookHUD_AddEntity();
    ESP_Reset();
    g_HooksInstalled = false;
}

static BOOL WINAPI hk_wglSwapBuffers(HDC hdc)
{
    g_InSwap = true;
    HookManager::UnhookInline(g_SwapAddr, g_SwapBytes);

    if (!g_Initialized) {
        g_GameHwnd = WindowFromDC(hdc);
        if (g_GameHwnd) {
            GUI::Init(g_GameHwnd);
            g_Offsets.Initialize();
            InstallGameHooks();
            g_Initialized = true;
        }
    }

    if (g_Initialized && !g_ShouldUnload)
    {
        RECT rc;
        GetClientRect(g_GameHwnd, &rc);
        int w = rc.right - rc.left;
        int h = rc.bottom - rc.top;

        Render::Begin2D(w, h);
        if (ESPSettings::espEnabled)
            DrawESP(w, h);
        Render::End2D();

        GUI::Render(w, h);

        if (Unload::IsRequested())
            Unload::ExecuteNow();
    }

    BOOL ret = o_wglSwapBuffers(hdc);

    if (!g_ShouldUnload)
        HookManager::HookInline(g_SwapAddr, hk_wglSwapBuffers, g_SwapBytes);

    g_InSwap = false;
    return ret;
}

static DWORD WINAPI MainThread(LPVOID)
{
    while (!GetModuleHandleA("opengl32.dll")) Sleep(100);
    while (!GetModuleHandleA("client.dll"))   Sleep(100);
    Sleep(2000);

    HMODULE hGL = GetModuleHandleA("opengl32.dll");
    if (!hGL) return 0;
    g_SwapAddr = GetProcAddress(hGL, "wglSwapBuffers");
    if (!g_SwapAddr) return 0;

    o_wglSwapBuffers = (wglSwapBuffers_t)g_SwapAddr;
    HookManager::HookInline(g_SwapAddr, hk_wglSwapBuffers, g_SwapBytes);

    while (!g_ShouldUnload) Sleep(50);

    Sleep(500);
    for (int i = 0; i < 100 && g_InSwap; i++) Sleep(20);

    RemoveGameHooks();
    if (g_Initialized) GUI::Shutdown();
    HookManager::UnhookInline(g_SwapAddr, g_SwapBytes);

    Sleep(1000);
    FreeLibraryAndExitThread(g_hModule, 0);
    return 0;
}

void Hooks_Init(HMODULE hModule)
{
    g_hModule = hModule;
    CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
}

void Hooks_Shutdown()
{
    g_ShouldUnload = true;
}