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
#if !defined( EVENT_FLAGSH )
#define EVENT_FLAGSH
#ifdef _WIN32
#pragma once
#endif

#define FEV_NOTHOST		(1<<0)    

#define FEV_RELIABLE	(1<<1)	 

#define FEV_GLOBAL		(1<<2)

#define FEV_UPDATE		(1<<3)

#define	FEV_HOSTONLY	(1<<4)

#define FEV_SERVER		(1<<5)

#define FEV_CLIENT		(1<<6)

#endif