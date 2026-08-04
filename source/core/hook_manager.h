#pragma once
#include <Windows.h>
#include <cstring>

namespace HookManager
{
    inline bool HookInline(void* target, void* hook, BYTE* backup, int len = 5)
    {
        if (!target || !hook || !backup) return false;
        DWORD old;
        if (!VirtualProtect(target, len, PAGE_EXECUTE_READWRITE, &old)) return false;
        memcpy(backup, target, len);
        BYTE jmp[5] = { 0xE9 };
        uintptr_t rel = (uintptr_t)hook - (uintptr_t)target - 5;
        memcpy(&jmp[1], &rel, 4);
        memcpy(target, jmp, 5);
        VirtualProtect(target, len, old, &old);
        return true;
    }

    inline bool UnhookInline(void* target, BYTE* backup, int len = 5)
    {
        if (!target || !backup) return false;
        DWORD old;
        if (!VirtualProtect(target, len, PAGE_EXECUTE_READWRITE, &old)) return false;
        memcpy(target, backup, len);
        VirtualProtect(target, len, old, &old);
        return true;
    }

    inline bool HookIAT(uintptr_t addr, void* hook, void** orig)
    {
        __try {
            uintptr_t val = *(uintptr_t*)addr;
            if (!val || val < 0x10000) return false;
            DWORD old;
            if (!VirtualProtect((LPVOID)addr, sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &old))
                return false;
            *orig = (void*)val;
            *(uintptr_t*)addr = (uintptr_t)hook;
            VirtualProtect((LPVOID)addr, sizeof(uintptr_t), old, &old);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    }

    inline bool UnhookIAT(uintptr_t addr, void* orig)
    {
        if (!orig || !addr) return false;
        DWORD old;
        if (!VirtualProtect((LPVOID)addr, sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &old))
            return false;
        *(uintptr_t*)addr = (uintptr_t)orig;
        VirtualProtect((LPVOID)addr, sizeof(uintptr_t), old, &old);
        return true;
    }
}