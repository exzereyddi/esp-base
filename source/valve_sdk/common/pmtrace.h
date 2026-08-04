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
#if !defined( PMTRACEH )
#define PMTRACEH
#ifdef _WIN32
#pragma once
#endif

typedef struct
{
	vec3_t	normal;
	float	dist;
} pmplane_t;

typedef struct pmtrace_s pmtrace_t;

struct pmtrace_s
{
	qboolean	allsolid;
	qboolean	startsolid;
	qboolean	inopen, inwater;
	float		fraction;
	vec3_t		endpos;
	pmplane_t	plane;
	int			ent;
	vec3_t      deltavelocity;
	int         hitgroup;
};

#endif