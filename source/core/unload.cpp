#include "pch.h"
#include "unload.h"
#include "hooks.h"
#include "gui/gui.h"
#include "visuals/esp.h"

namespace Unload
{
    static volatile bool s_Requested = false;

    void Request() { s_Requested = true; }
    bool IsRequested() { return s_Requested; }

    void ExecuteNow()
    {
        if (g_ShouldUnload) return;

        ESPSettings::espEnabled = false;
        GUI::g_IsOpen = false;
        ShowCursor(TRUE);
        ESP_Reset();

        g_ShouldUnload = true;
    }
}