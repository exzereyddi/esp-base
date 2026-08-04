
#if !defined( COM_MODEL_H )
#define COM_MODEL_H
#if defined( _WIN32 )
#pragma once
#endif

#define STUDIO_RENDER 1
#define STUDIO_EVENTS 2

#define MAX_CLIENTS			32
#define	MAX_EDICTS			900

#define MAX_MODEL_NAME		64
#define MAX_MAP_HULLS		4
#define	MIPLEVELS			4
#define	NUM_AMBIENTS		4
#define	MAXLIGHTMAPS		4
#define	PLANE_ANYZ			5

#define ALIAS_Z_CLIP_PLANE	5

#define ALIAS_LEFT_CLIP				0x0001
#define ALIAS_TOP_CLIP				0x0002
#define ALIAS_RIGHT_CLIP			0x0004
#define ALIAS_BOTTOM_CLIP			0x0008
#define ALIAS_Z_CLIP				0x0010
#define ALIAS_ONSEAM				0x0020
#define ALIAS_XY_CLIP_MASK			0x000F

#define	ZISCALE	((float)0x8000)

#define CACHE_SIZE	32

typedef enum
{
	mod_brush, 
	mod_sprite, 
	mod_alias, 
	mod_studio
} modtype_t;

#ifndef SYNCTYPE_T
#define SYNCTYPE_T

typedef enum
{
	ST_SYNC=0,
	ST_RAND
} synctype_t;

#endif

typedef struct
{
	float		mins[3], maxs[3];
	float		origin[3];
	int			headnode[MAX_MAP_HULLS];
	int			visleafs;
	int			firstface, numfaces;
} dmodel_t;

typedef struct mplane_s
{
	vec3_t	normal;
	float	dist;
	byte	type;
	byte	signbits;
	byte	pad[2];
} mplane_t;

typedef struct
{
	vec3_t		position;
} mvertex_t;

typedef struct
{
	unsigned short	v[2];
	unsigned int	cachededgeoffset;
} medge_t;

typedef struct texture_s
{
	char		name[16];
	unsigned	width, height;
	int			anim_total;
	int			anim_min, anim_max;
	struct texture_s *anim_next;
	struct texture_s *alternate_anims;
	unsigned	offsets[MIPLEVELS];
	unsigned	paloffset;
} texture_t;

typedef struct
{
	float		vecs[2][4];
	float		mipadjust;
	texture_t	*texture;
	int			flags;
} mtexinfo_t;

typedef struct mnode_s
{
	int			contents;
	int			visframe;
	
	short		minmaxs[6];

	struct mnode_s	*parent;

	mplane_t	*plane;
	struct mnode_s	*children[2];	

	unsigned short		firstsurface;
	unsigned short		numsurfaces;
} mnode_t;

typedef struct msurface_s	msurface_t;
typedef struct decal_s		decal_t;

struct decal_s
{
	decal_t		*pnext;
	msurface_t	*psurface;
	short		dx;
	short		dy;
	short		texture;
	byte		scale;
	byte		flags;

	short		entityIndex;
};

typedef struct mleaf_s
{
	int			contents;
	int			visframe;

	short		minmaxs[6];

	struct mnode_s	*parent;

	byte		*compressed_vis;
	struct efrag_s	*efrags;

	msurface_t	**firstmarksurface;
	int			nummarksurfaces;
	int			key;
	byte		ambient_sound_level[NUM_AMBIENTS];
} mleaf_t;

struct msurface_s
{
	int			visframe;

	int			dlightframe;
	int			dlightbits;

	mplane_t	*plane;
	int			flags;

	int			firstedge;
	int			numedges;
	
	struct surfcache_s	*cachespots[MIPLEVELS];

	short		texturemins[2];
	short		extents[2];

	mtexinfo_t	*texinfo;		
	
	byte		styles[MAXLIGHTMAPS];
	color24		*samples;
	
	decal_t		*pdecals;
};

typedef struct
{
	int			planenum;
	short		children[2];
} dclipnode_t;

typedef struct hull_s
{
	dclipnode_t	*clipnodes;
	mplane_t	*planes;
	int			firstclipnode;
	int			lastclipnode;
	vec3_t		clip_mins;
	vec3_t		clip_maxs;
} hull_t;

#if !defined( CACHE_USER ) && !defined( QUAKEDEF_H )
#define CACHE_USER
typedef struct cache_user_s
{
	void	*data;
} cache_user_t;
#endif

typedef struct model_s
{
	char		name[ MAX_MODEL_NAME ];
	qboolean	needload;

	modtype_t	type;
	int			numframes;
	synctype_t	synctype;
	
	int			flags;

	vec3_t		mins, maxs;
	float		radius;

	int			firstmodelsurface, nummodelsurfaces;

	int			numsubmodels;
	dmodel_t	*submodels;

	int			numplanes;
	mplane_t	*planes;

	int			numleafs;
	struct mleaf_s		*leafs;

	int			numvertexes;
	mvertex_t	*vertexes;

	int			numedges;
	medge_t		*edges;

	int			numnodes;
	mnode_t		*nodes;

	int			numtexinfo;
	mtexinfo_t	*texinfo;

	int			numsurfaces;
	msurface_t	*surfaces;

	int			numsurfedges;
	int			*surfedges;

	int			numclipnodes;
	dclipnode_t	*clipnodes;

	int			nummarksurfaces;
	msurface_t	**marksurfaces;

	hull_t		hulls[MAX_MAP_HULLS];

	int			numtextures;
	texture_t	**textures;

	byte		*visdata;

	color24		*lightdata;

	char		*entities;

	cache_user_t	cache;

} model_t;

typedef vec_t vec4_t[4];

typedef struct alight_s
{
	int			ambientlight;
	int			shadelight;
	vec3_t		color;
	float		*plightvec;
} alight_t;

typedef struct auxvert_s
{
	float	fv[3];
} auxvert_t;

#include "engine/custom.h"

#define	MAX_INFO_STRING			256
#define	MAX_SCOREBOARDNAME		32
typedef struct player_info_s
{
	int		userid;

	char	userinfo[ MAX_INFO_STRING ];

	char	name[ MAX_SCOREBOARDNAME ];

	int		spectator;

	int		ping;
	int		packet_loss;

	char	model[MAX_QPATH];
	int		topcolor;
	int		bottomcolor;

	int		renderframe;	

	int		gaitsequence;
	float	gaitframe;
	float	gaityaw;
	vec3_t	prevgaitorigin;

	customization_t customdata;
} player_info_t;

#endif