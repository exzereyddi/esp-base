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
#ifndef SHAKE_H
#define SHAKE_H


extern int gmsgShake;

typedef struct
{
	unsigned short	amplitude;
	unsigned short 	duration;
	unsigned short	frequency;
} ScreenShake;

extern void V_ApplyShake( float *origin, float *angles, float factor );
extern void V_CalcShake( void );
extern int V_ScreenShake( const char *pszName, int iSize, void *pbuf );
extern int V_ScreenFade( const char *pszName, int iSize, void *pbuf );

extern int gmsgFade;

#define FFADE_IN			0x0000
#define FFADE_OUT			0x0001
#define FFADE_MODULATE		0x0002
#define FFADE_STAYOUT		0x0004
#define FFADE_LONGFADE		0x0008


typedef struct
{
	unsigned short 	duration;
	unsigned short 	holdTime;
	short			fadeFlags;
	byte			r, g, b, a;
} ScreenFade;

#endif