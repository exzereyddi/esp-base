#include "pch.h"
#include "offsets.h"

COffsets g_Offsets;

bool COffsets::Initialize()
{
    if (!FindModules())  return false;
    if (!FindOffsets())  return false;
    return true;
}

bool COffsets::FindModuleByName(const char* name, Module* module)
{
    HMODULE hMod = GetModuleHandleA(name);
    if (!hMod) return false;
    MEMORY_BASIC_INFORMATION mem;
    if (!VirtualQuery(hMod, &mem, sizeof(mem))) return false;
    IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)mem.AllocationBase;
    IMAGE_NT_HEADERS* pe = (IMAGE_NT_HEADERS*)((uintptr_t)dos + dos->e_lfanew);
    if (pe->Signature != IMAGE_NT_SIGNATURE) return false;
    module->handle = hMod;
    module->base = (uintptr_t)mem.AllocationBase;
    module->size = pe->OptionalHeader.SizeOfImage;
    module->end = module->base + module->size - 1;
    return true;
}

bool COffsets::FindModules()
{
    if (!FindModuleByName("hw.dll", &hw))
        if (!FindModuleByName("engine.dll", &hw)) return false;
    if (!FindModuleByName("client.dll", &client)) return false;
    return true;
}

bool COffsets::FindEngineFunc()
{
    FARPROC fn = GetProcAddress(client.handle, "Initialize");
    if (!fn) return false;
    uintptr_t addr = (uintptr_t)fn;
    for (int i = 0; i < 0x40; i++) {
        unsigned char* b = (unsigned char*)(addr + i);
        if (b[0] == 0xBF && b[5] == 0xF3 && b[6] == 0xA5) {
            pEngineFunc = *(cl_enginefunc_t**)(addr + i + 1);
            return true;
        }
    }
    return false;
}

uintptr_t COffsets::FindPlayerMove()
{
    uintptr_t ptr = FindString(hw.base, hw.end, "ScreenFade");
    if (!ptr) return 0;
    ptr = FindReference(hw.base, hw.end, ptr);
    if (!ptr) return 0;
    uintptr_t addr = ptr + 0x18;
    if (addr < hw.base || addr > hw.end) return 0;
    return *(uintptr_t*)addr;
}

bool COffsets::FindOffsets()
{
    pmove = (playermove_t*)FindPlayerMove();
    if (!pmove) return false;
    FindEngineFunc();
    return true;
}

uintptr_t COffsets::FindPattern(uintptr_t start, uintptr_t end,
    const char* pattern, const char* mask)
{
    size_t len = strlen(mask);
    for (uintptr_t i = start; i < end - len; i++) {
        bool found = true;
        for (size_t j = 0; j < len; j++) {
            if (mask[j] == 'x' && pattern[j] != *(char*)(i + j)) { found = false; break; }
        }
        if (found) return i;
    }
    return 0;
}

uintptr_t COffsets::FindString(uintptr_t start, uintptr_t end, const char* str)
{
    size_t len = strlen(str);
    for (uintptr_t i = start; i < end - len; i++)
        if (memcmp((void*)i, str, len) == 0) return i;
    return 0;
}

uintptr_t COffsets::FindReference(uintptr_t start, uintptr_t end, uintptr_t addr)
{
    char pattern[5] = { 0x68, 0, 0, 0, 0 };
    *(uintptr_t*)&pattern[1] = addr;
    for (uintptr_t i = start; i < end - 5; i++)
        if (memcmp((void*)i, pattern, 5) == 0) return i;
    return 0;
}