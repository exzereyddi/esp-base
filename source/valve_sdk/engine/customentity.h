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
#ifndef CUSTOMENTITY_H
#define CUSTOMENTITY_H


#define BEAMENT_ENTITY(x)		((x)&0xFFF)
#define BEAMENT_ATTACHMENT(x)	(((x)>>12)&0xF)

enum 
{
	BEAM_POINTS = 0,
	BEAM_ENTPOINT,
	BEAM_ENTS,
	BEAM_HOSE,
};

#define BEAM_FSINE		0x10
#define BEAM_FSOLID		0x20
#define BEAM_FSHADEIN	0x40
#define BEAM_FSHADEOUT	0x80

#endif