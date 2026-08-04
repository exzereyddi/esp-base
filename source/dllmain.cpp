#include "pch.h"
#include "core/hooks.h"

static HMODULE g_hModule = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        g_hModule = hModule;
        Hooks_Init(hModule);
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        Hooks_Shutdown();
    }
    return TRUE;
}