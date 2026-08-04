#pragma once
#include <Windows.h>

extern volatile bool g_ShouldUnload;

void Hooks_Init(HMODULE hModule);
void Hooks_Shutdown();