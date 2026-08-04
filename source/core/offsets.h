#pragma once
#include <Windows.h>
#include <cstdint>

#define MAX_PLAYERS 32

struct Module {
    HMODULE   handle;
    uintptr_t base;
    uintptr_t size;
    uintptr_t end;
};

#include "valve_sdk/sdk.h"

typedef struct physent_s {
    char          name[32];
    int           player;
    vec3_t        origin;
    struct model_s* model;
    struct model_s* studiomodel;
    vec3_t        mins;
    vec3_t        maxs;
    int           info;
    vec3_t        angles;
    int           solid;
    int           skin;
    int           rendermode;
    float         frame;
    int           sequence;
    byte          controller[4];
    byte          blending[2];
    int           movetype;
    int           takedamage;
    int           blooddecal;
    int           team;
    int           classnumber;
    int           iuser1, iuser2, iuser3, iuser4;
    float         fuser1, fuser2, fuser3, fuser4;
    vec3_t        vuser1, vuser2, vuser3, vuser4;
} physent_t;

typedef struct playermove_s {
    int    player_index;
    int    server;
    int    multiplayer;
    float  time;
    float  frametime;
    vec3_t forward, right, up;
    vec3_t origin;
    vec3_t angles;
    vec3_t oldangles;
    vec3_t velocity;
    vec3_t movedir;
    vec3_t basevelocity;
    vec3_t view_ofs;
    float  flDuckTime;
    int    bInDuck;
    int    flTimeStepSound;
    int    iStepLeft;
    float  flFallVelocity;
    vec3_t punchangle;
    float  flSwimTime;
    float  flNextPrimaryAttack;
    int    effects;
    int    flags;
    int    usehull;
    float  gravity;
    float  friction;
    int    oldbuttons;
    float  waterjumptime;
    int    dead;
    int    deadflag;
    int    spectator;
    int    movetype;
    int    onground;
    int    waterlevel;
    int    watertype;
    int    oldwaterlevel;
    char   sztexturename[256];
    char   chtexturetype;
    float  maxspeed;
    float  clientmaxspeed;
    int    numphysent;
    physent_t physents[600];
    struct movevars_s* movevars;
} playermove_t;

class COffsets {
public:
    Module hw;
    Module client;

    playermove_t* pmove = nullptr;
    cl_enginefunc_t* pEngineFunc = nullptr;

    bool Initialize();

    uintptr_t FindPattern(uintptr_t start, uintptr_t end,
        const char* pattern, const char* mask);
    uintptr_t FindString(uintptr_t start, uintptr_t end, const char* str);
    uintptr_t FindReference(uintptr_t start, uintptr_t end, uintptr_t addr);

private:
    bool FindModuleByName(const char* name, Module* module);
    bool FindModules();
    bool FindOffsets();
    bool FindEngineFunc();
    uintptr_t FindPlayerMove();
};

extern COffsets g_Offsets;