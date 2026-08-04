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
#pragma once

#ifndef CUSTOM_H
#define CUSTOM_H
#ifdef _WIN32
#pragma once
#endif

#include "common/const.h"

#define MAX_QPATH 64

typedef enum
{
	t_sound = 0,
	t_skin,
	t_model,
	t_decal,
	t_generic,
	t_eventscript,
	t_world,
} resourcetype_t;


typedef struct
{
	int				size;
} _resourceinfo_t;

typedef struct resourceinfo_s
{
	_resourceinfo_t info[ 8 ];
} resourceinfo_t;

#define RES_FATALIFMISSING (1<<0)
#define RES_WASMISSING     (1<<1)
#define RES_CUSTOM         (1<<2)
#define RES_REQUESTED	   (1<<3)
#define RES_PRECACHED	   (1<<4)
#define RES_ALWAYS		   (1<<5)
#define RES_CHECKFILE	   (1<<7)

#include "common/crc.h"

typedef struct resource_s
{
	char              szFileName[MAX_QPATH];
	resourcetype_t    type;
	int               nIndex;
	int               nDownloadSize;
	unsigned char     ucFlags;

	unsigned char     rgucMD5_hash[16];
	unsigned char     playernum;

	unsigned char	  rguc_reserved[ 32 ];
	struct resource_s *pNext;
	struct resource_s *pPrev;
} resource_t;

typedef struct customization_s
{
	qboolean bInUse;
	resource_t resource;
	qboolean bTranslated;
	int        nUserData1;
	int        nUserData2;
	void *pInfo;
	void *pBuffer;
	struct customization_s *pNext;
} customization_t;

#define FCUST_FROMHPAK		( 1<<0 )
#define FCUST_WIPEDATA		( 1<<1 )
#define FCUST_IGNOREINIT	( 1<<2 )

void		COM_ClearCustomizationList( struct customization_s *pHead, qboolean bCleanDecals);
qboolean	COM_CreateCustomization( struct customization_s *pListHead, struct resource_s *pResource, int playernumber, int flags, 
				struct customization_s **pCustomization, int *nLumps ); 
int			COM_SizeofResourceList ( struct resource_s *pList, struct resourceinfo_s *ri );

#endif