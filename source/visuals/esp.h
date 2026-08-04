#pragma once
#include <Windows.h>
#include <vector>

struct vec3 { float x, y, z; };
struct vec2 { float x, y; };

struct ESPPlayerData {
    vec3 head;
    vec3 feet;
    int  team;
    int  index;
    char name[32];
};

namespace ESPSettings {
    extern bool  espEnabled;
    extern bool  espBox;
    extern bool  espName;
    extern bool  espTeammates;
    extern bool  espVisibleOnly;
    extern float espColorCT[4];
    extern float espColorT[4];
}

void ESP_AddPlayer(const ESPPlayerData& data);
void ESP_Reset();
void DrawESP(int winW, int winH);