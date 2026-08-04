/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#if !defined( CL_ENTITYH )
#define CL_ENTITYH
#ifdef _WIN32
#pragma once
#endif

typedef struct efrag_s
{
	struct mleaf_s		*leaf;
	struct efrag_s		*leafnext;
	struct cl_entity_s	*entity;
	struct efrag_s		*entnext;
} efrag_t;

typedef struct
{
	byte					mouthopen;
	byte					sndcount;
	int						sndavg;
} mouth_t;

typedef struct
{
	float					prevanimtime;  
	float					sequencetime;
	byte					prevseqblending[2];
	vec3_t					prevorigin;
	vec3_t					prevangles;

	int						prevsequence;
	float					prevframe;

	byte					prevcontroller[4];
	byte					prevblending[2];
} latchedvars_t;

typedef struct
{
	float					animtime;

	vec3_t					origin;
	vec3_t					angles;
} position_history_t;

typedef struct cl_entity_s cl_entity_t;

#define HISTORY_MAX		64
#define HISTORY_MASK	( HISTORY_MAX - 1 )


#if !defined( ENTITY_STATEH )
#include "entity_state.h"
#endif

#if !defined( PROGS_H )
#include "engine/progs.h"
#endif

struct cl_entity_s
{
	int						index;

	qboolean				player;
	
	entity_state_t			baseline;
	entity_state_t			prevstate;
	entity_state_t			curstate;

	int						current_position;
	position_history_t		ph[ HISTORY_MAX ];

	mouth_t					mouth;

	latchedvars_t			latched;

	float					lastmove;

	vec3_t					origin;
	vec3_t					angles;

	vec3_t					attachment[4];

	int						trivial_accept;

	struct model_s			*model;
	struct efrag_s			*efrag;
	struct mnode_s			*topnode;

	float					syncbase;
	int						visframe;
	colorVec				cvFloorColor;
};

#endif