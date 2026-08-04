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
#ifndef CVARDEF_H
#define CVARDEF_H

#define	FCVAR_ARCHIVE		(1<<0)
#define	FCVAR_USERINFO		(1<<1)
#define	FCVAR_SERVER		(1<<2)
#define FCVAR_EXTDLL		(1<<3)
#define FCVAR_CLIENTDLL     (1<<4)
#define FCVAR_PROTECTED     (1<<5)
#define FCVAR_SPONLY        (1<<6)
#define FCVAR_PRINTABLEONLY (1<<7)
#define FCVAR_UNLOGGED		(1<<8)
#define FCVAR_NOEXTRAWHITEPACE	(1<<9)
#define FCVAR_PRIVILEGED	(1<<10)
#define FCVAR_FILTERSTUFFTEXT	(1<<11)
#define FCVAR_FILTERCHARS	(1<<12)
#define FCVAR_NOBADPATHS	(1<<13)

typedef struct cvar_s
{
	char	*name;
	char	*string;
	int		flags;
	float	value;
	struct cvar_s *next;
} cvar_t;
#endif