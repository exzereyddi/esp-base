#if !defined( R_STUDIOINT_H )
#define R_STUDIOINT_H
#if defined( _WIN32 )
#pragma once
#endif

#define STUDIO_INTERFACE_VERSION 1

typedef struct engine_studio_api_s
{
	void			*( *Mem_Calloc )				( int number, size_t size );
	void			*( *Cache_Check )				( struct cache_user_s *c );
	void			( *LoadCacheFile )				( char *path, struct cache_user_s *cu );
	struct model_s	*( *Mod_ForName )				( const char *name, int crash_if_missing );
	void			*( *Mod_Extradata )				( struct model_s *mod );
	struct model_s	*( *GetModelByIndex )			( int index );
	struct cl_entity_s * ( *GetCurrentEntity )		( void );
	struct player_info_s *( *PlayerInfo )			( int index );
	struct entity_state_s *( *GetPlayerState )		( int index );
	struct cl_entity_s * ( *GetViewEntity )			( void );
	void			( *GetTimes )					( int *framecount, double *current, double *old );
	struct cvar_s	*( *GetCvar )					( const char *name );
	void			( *GetViewInfo )				( float *origin, float *upv, float *rightv, float *vpnv );
	struct model_s	*( *GetChromeSprite )			( void );
	void			( *GetModelCounters )			( int **s, int **a );
	void			( *GetAliasScale )				( float *x, float *y );

	float			****( *StudioGetBoneTransform ) ( void );
	float			****( *StudioGetLightTransform )( void );
	float			***( *StudioGetAliasTransform ) ( void );
	float			***( *StudioGetRotationMatrix ) ( void );

	void			( *StudioSetupModel )			( int bodypart, void **ppbodypart, void **ppsubmodel );
	int				( *StudioCheckBBox )			( void );
	void			( *StudioDynamicLight )			( struct cl_entity_s *ent, struct alight_s *plight );
	void			( *StudioEntityLight )			( struct alight_s *plight );
	void			( *StudioSetupLighting )		( struct alight_s *plighting );

	void			( *StudioDrawPoints )			( void );

	void			( *StudioDrawHulls )			( void );
	void			( *StudioDrawAbsBBox )			( void );
	void			( *StudioDrawBones )			( void );
	void			( *StudioSetupSkin )			( void *ptexturehdr, int index );
	void			( *StudioSetRemapColors )		( int top, int bottom );
	struct model_s	*( *SetupPlayerModel )			( int index );
	void			( *StudioClientEvents )			( void );
	int				( *GetForceFaceFlags )			( void );
	void			( *SetForceFaceFlags )			( int flags );
	void			( *StudioSetHeader )			( void *header );
	void			( *SetRenderModel )				( struct model_s *model );

	void			( *SetupRenderer )				( int rendermode );
	void			( *RestoreRenderer )			( void );

	void			( *SetChromeOrigin )			( void );

	int				( *IsHardware )					( void );
	
	void			( *GL_StudioDrawShadow )		( void );
	void			( *GL_SetRenderMode )			( int mode );

	void			( *StudioSetRenderamt )			(int iRenderamt);
	void			( *StudioSetCullState )			( int iCull	   );
	void			( *StudioRenderShadow )			( int iSprite, float *p1, float *p2, float *p3, float *p4 );
} engine_studio_api_t;

typedef struct server_studio_api_s
{
	void			*( *Mem_Calloc )				( int number, size_t size );
	void			*( *Cache_Check )				( struct cache_user_s *c );
	void			( *LoadCacheFile )				( char *path, struct cache_user_s *cu );
	void			*( *Mod_Extradata )				( struct model_s *mod );
} server_studio_api_t;


typedef struct r_studio_interface_s
{
	int				version;
	int				( *StudioDrawModel	)			( int flags );
	int				( *StudioDrawPlayer	)			( int flags, struct entity_state_s *pplayer );
} r_studio_interface_t;

extern r_studio_interface_t *pStudioAPI;

#define SV_BLENDING_INTERFACE_VERSION 1

typedef struct sv_blending_interface_s
{
	int				version;

	void			( *SV_StudioSetupBones )		( struct model_s	*pModel, 
													  float				frame, 
													  int				sequence, 
													  const vec3_t		angles, 
													  const	vec3_t		origin, 
													  const	byte		*pcontroller,
													  const	byte		*pblending, 
													  int				iBone,
													  const edict_t		*pEdict );
} sv_blending_interface_t;

#endif