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
#ifndef EIFACE_H
#define EIFACE_H

#include "archtypes.h"

#ifdef HLDEMO_BUILD
#define INTERFACE_VERSION       001
#else
#define INTERFACE_VERSION		140
#endif

#include <stdio.h>
#include "engine/custom.h"
#include "cvardef.h"
#include "Sequence.h"

/*
#ifdef _WIN32
#define DLLEXPORT __stdcall
#else
#define DLLEXPORT  __attribute__ ((visibility("default")))
#endif
*/

typedef enum
	{
	at_notice,
	at_console,
	at_aiconsole,
	at_warning,
	at_error,
	at_logged
	} ALERT_TYPE;

typedef enum
	{
	print_console,
	print_center,
	print_chat,
	} PRINT_TYPE;

typedef enum
{
	force_exactfile,
	force_model_samebounds,
	force_model_specifybounds,
	force_model_specifybounds_if_avail,
} FORCE_TYPE;

typedef struct
	{
	int		fAllSolid;
	int		fStartSolid;
	int		fInOpen;
	int		fInWater;
	float	flFraction;
	vec3_t	vecEndPos;
	float	flPlaneDist;
	vec3_t	vecPlaneNormal;
	edict_t	*pHit;
	int		iHitgroup;
	} TraceResult;

typedef struct 
{
	int	fPlaying;
	int	fWasPlaying;
	int	fInitialized;
	int	fEnabled;
	int	fPlayLooping;
	float	cdvolume;
	int	fCDRom;
	int	fPlayTrack;
} CDStatus;

#include "common/crc.h"


typedef struct enginefuncs_s
{
	int			(*pfnPrecacheModel)			(char* s);
	int			(*pfnPrecacheSound)			(char* s);
	void		(*pfnSetModel)				(edict_t *e, const char *m);
	int			(*pfnModelIndex)			(const char *m);
	int			(*pfnModelFrames)			(int modelIndex);
	void		(*pfnSetSize)				(edict_t *e, const float *rgflMin, const float *rgflMax);
	void		(*pfnChangeLevel)			(char* s1, char* s2);
	void		(*pfnGetSpawnParms)			(edict_t *ent);
	void		(*pfnSaveSpawnParms)		(edict_t *ent);
	float		(*pfnVecToYaw)				(const float *rgflVector);
	void		(*pfnVecToAngles)			(const float *rgflVectorIn, float *rgflVectorOut);
	void		(*pfnMoveToOrigin)			(edict_t *ent, const float *pflGoal, float dist, int iMoveType);
	void		(*pfnChangeYaw)				(edict_t* ent);
	void		(*pfnChangePitch)			(edict_t* ent);
	edict_t*	(*pfnFindEntityByString)	(edict_t *pEdictStartSearchAfter, const char *pszField, const char *pszValue);
	int			(*pfnGetEntityIllum)		(edict_t* pEnt);
	edict_t*	(*pfnFindEntityInSphere)	(edict_t *pEdictStartSearchAfter, const float *org, float rad);
	edict_t*	(*pfnFindClientInPVS)		(edict_t *pEdict);
	edict_t* (*pfnEntitiesInPVS)			(edict_t *pplayer);
	void		(*pfnMakeVectors)			(const float *rgflVector);
	void		(*pfnAngleVectors)			(const float *rgflVector, float *forward, float *right, float *up);
	edict_t*	(*pfnCreateEntity)			(void);
	void		(*pfnRemoveEntity)			(edict_t* e);
	edict_t*	(*pfnCreateNamedEntity)		(int className);
	void		(*pfnMakeStatic)			(edict_t *ent);
	int			(*pfnEntIsOnFloor)			(edict_t *e);
	int			(*pfnDropToFloor)			(edict_t* e);
	int			(*pfnWalkMove)				(edict_t *ent, float yaw, float dist, int iMode);
	void		(*pfnSetOrigin)				(edict_t *e, const float *rgflOrigin);
	void		(*pfnEmitSound)				(edict_t *entity, int channel, const char *sample, /*int*/float volume, float attenuation, int fFlags, int pitch);
	void		(*pfnEmitAmbientSound)		(edict_t *entity, float *pos, const char *samp, float vol, float attenuation, int fFlags, int pitch);
	void		(*pfnTraceLine)				(const float *v1, const float *v2, int fNoMonsters, edict_t *pentToSkip, TraceResult *ptr);
	void		(*pfnTraceToss)				(edict_t* pent, edict_t* pentToIgnore, TraceResult *ptr);
	int			(*pfnTraceMonsterHull)		(edict_t *pEdict, const float *v1, const float *v2, int fNoMonsters, edict_t *pentToSkip, TraceResult *ptr);
	void		(*pfnTraceHull)				(const float *v1, const float *v2, int fNoMonsters, int hullNumber, edict_t *pentToSkip, TraceResult *ptr);
	void		(*pfnTraceModel)			(const float *v1, const float *v2, int hullNumber, edict_t *pent, TraceResult *ptr);
	const char *(*pfnTraceTexture)			(edict_t *pTextureEntity, const float *v1, const float *v2 );
	void		(*pfnTraceSphere)			(const float *v1, const float *v2, int fNoMonsters, float radius, edict_t *pentToSkip, TraceResult *ptr);
	void		(*pfnGetAimVector)			(edict_t* ent, float speed, float *rgflReturn);
	void		(*pfnServerCommand)			(char* str);
	void		(*pfnServerExecute)			(void);
	void		(*pfnClientCommand)			(edict_t* pEdict, char* szFmt, ...);
	void		(*pfnParticleEffect)		(const float *org, const float *dir, float color, float count);
	void		(*pfnLightStyle)			(int style, char* val);
	int			(*pfnDecalIndex)			(const char *name);
	int			(*pfnPointContents)			(const float *rgflVector);
	void		(*pfnMessageBegin)			(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed);
	void		(*pfnMessageEnd)			(void);
	void		(*pfnWriteByte)				(int iValue);
	void		(*pfnWriteChar)				(int iValue);
	void		(*pfnWriteShort)			(int iValue);
	void		(*pfnWriteLong)				(int iValue);
	void		(*pfnWriteAngle)			(float flValue);
	void		(*pfnWriteCoord)			(float flValue);
	void		(*pfnWriteString)			(const char *sz);
	void		(*pfnWriteEntity)			(int iValue);
	void		(*pfnCVarRegister)			(cvar_t *pCvar);
	float		(*pfnCVarGetFloat)			(const char *szVarName);
	const char*	(*pfnCVarGetString)			(const char *szVarName);
	void		(*pfnCVarSetFloat)			(const char *szVarName, float flValue);
	void		(*pfnCVarSetString)			(const char *szVarName, const char *szValue);
	void		(*pfnAlertMessage)			(ALERT_TYPE atype, char *szFmt, ...);
	void		(*pfnEngineFprintf)			(void *pfile, char *szFmt, ...);
	void*		(*pfnPvAllocEntPrivateData)	(edict_t *pEdict, int32 cb);
	void*		(*pfnPvEntPrivateData)		(edict_t *pEdict);
	void		(*pfnFreeEntPrivateData)	(edict_t *pEdict);
	const char*	(*pfnSzFromIndex)			(int iString);
	int			(*pfnAllocString)			(const char *szValue);
	struct entvars_s*	(*pfnGetVarsOfEnt)			(edict_t *pEdict);
	edict_t*	(*pfnPEntityOfEntOffset)	(int iEntOffset);
	int			(*pfnEntOffsetOfPEntity)	(const edict_t *pEdict);
	int			(*pfnIndexOfEdict)			(const edict_t *pEdict);
	edict_t*	(*pfnPEntityOfEntIndex)		(int iEntIndex);
	edict_t*	(*pfnFindEntityByVars)		(struct entvars_s* pvars);
	void*		(*pfnGetModelPtr)			(edict_t* pEdict);
	int			(*pfnRegUserMsg)			(const char *pszName, int iSize);
	void		(*pfnAnimationAutomove)		(const edict_t* pEdict, float flTime);
	void		(*pfnGetBonePosition)		(const edict_t* pEdict, int iBone, float *rgflOrigin, float *rgflAngles );
	uint32 (*pfnFunctionFromName)	( const char *pName );
	const char *(*pfnNameForFunction)		( uint32 function );
	void		(*pfnClientPrintf)			( edict_t* pEdict, PRINT_TYPE ptype, const char *szMsg );
	void		(*pfnServerPrint)			( const char *szMsg );
	const char *(*pfnCmd_Args)				( void );
	const char *(*pfnCmd_Argv)				( int argc );
	int			(*pfnCmd_Argc)				( void );
	void		(*pfnGetAttachment)			(const edict_t *pEdict, int iAttachment, float *rgflOrigin, float *rgflAngles );
	void		(*pfnCRC32_Init)			(CRC32_t *pulCRC);
	void        (*pfnCRC32_ProcessBuffer)   (CRC32_t *pulCRC, void *p, int len);
	void		(*pfnCRC32_ProcessByte)     (CRC32_t *pulCRC, unsigned char ch);
	CRC32_t		(*pfnCRC32_Final)			(CRC32_t pulCRC);
	int32		(*pfnRandomLong)			(int32  lLow,  int32  lHigh);
	float		(*pfnRandomFloat)			(float flLow, float flHigh);
	void		(*pfnSetView)				(const edict_t *pClient, const edict_t *pViewent );
	float		(*pfnTime)					( void );
	void		(*pfnCrosshairAngle)		(const edict_t *pClient, float pitch, float yaw);
	byte *      (*pfnLoadFileForMe)         (char *filename, int *pLength);
	void        (*pfnFreeFile)              (void *buffer);
	void        (*pfnEndSection)            (const char *pszSectionName);
	int 		(*pfnCompareFileTime)       (char *filename1, char *filename2, int *iCompare);
	void        (*pfnGetGameDir)            (char *szGetGameDir);
	void		(*pfnCvar_RegisterVariable) (cvar_t *variable);
	void        (*pfnFadeClientVolume)      (const edict_t *pEdict, int fadePercent, int fadeOutSeconds, int holdTime, int fadeInSeconds);
	void        (*pfnSetClientMaxspeed)     (const edict_t *pEdict, float fNewMaxspeed);
	edict_t *	(*pfnCreateFakeClient)		(const char *netname);
	void		(*pfnRunPlayerMove)			(edict_t *fakeclient, const float *viewangles, float forwardmove, float sidemove, float upmove, unsigned short buttons, byte impulse, byte msec );
	int			(*pfnNumberOfEntities)		(void);
	char*		(*pfnGetInfoKeyBuffer)		(edict_t *e);
	char*		(*pfnInfoKeyValue)			(char *infobuffer, char *key);
	void		(*pfnSetKeyValue)			(char *infobuffer, char *key, char *value);
	void		(*pfnSetClientKeyValue)		(int clientIndex, char *infobuffer, char *key, char *value);
	int			(*pfnIsMapValid)			(char *filename);
	void		(*pfnStaticDecal)			( const float *origin, int decalIndex, int entityIndex, int modelIndex );
	int			(*pfnPrecacheGeneric)		(char* s);
	int			(*pfnGetPlayerUserId)		(edict_t *e );
	void		(*pfnBuildSoundMsg)			(edict_t *entity, int channel, const char *sample, /*int*/float volume, float attenuation, int fFlags, int pitch, int msg_dest, int msg_type, const float *pOrigin, edict_t *ed);
	int			(*pfnIsDedicatedServer)		(void);
	cvar_t		*(*pfnCVarGetPointer)		(const char *szVarName);
	unsigned int (*pfnGetPlayerWONId)		(edict_t *e);

	void		(*pfnInfo_RemoveKey)		( char *s, const char *key );
	const char *(*pfnGetPhysicsKeyValue)	( const edict_t *pClient, const char *key );
	void		(*pfnSetPhysicsKeyValue)	( const edict_t *pClient, const char *key, const char *value );
	const char *(*pfnGetPhysicsInfoString)	( const edict_t *pClient );
	unsigned short (*pfnPrecacheEvent)		( int type, const char*psz );
	void		(*pfnPlaybackEvent)			( int flags, const edict_t *pInvoker, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2 );

	unsigned char *(*pfnSetFatPVS)			( float *org );
	unsigned char *(*pfnSetFatPAS)			( float *org );

	int			(*pfnCheckVisibility )		( const edict_t *entity, unsigned char *pset );

	void		(*pfnDeltaSetField)			( struct delta_s *pFields, const char *fieldname );
	void		(*pfnDeltaUnsetField)		( struct delta_s *pFields, const char *fieldname );
	void		(*pfnDeltaAddEncoder)		( char *name, void (*conditionalencode)( struct delta_s *pFields, const unsigned char *from, const unsigned char *to ) );
	int			(*pfnGetCurrentPlayer)		( void );
	int			(*pfnCanSkipPlayer)			( const edict_t *player );
	int			(*pfnDeltaFindField)		( struct delta_s *pFields, const char *fieldname );
	void		(*pfnDeltaSetFieldByIndex)	( struct delta_s *pFields, int fieldNumber );
	void		(*pfnDeltaUnsetFieldByIndex)( struct delta_s *pFields, int fieldNumber );

	void		(*pfnSetGroupMask)			( int mask, int op );

	int			(*pfnCreateInstancedBaseline) ( int classname, struct entity_state_s *baseline );
	void		(*pfnCvar_DirectSet)		( struct cvar_s *var, char *value );

	void		(*pfnForceUnmodified)		( FORCE_TYPE type, float *mins, float *maxs, const char *filename );

	void		(*pfnGetPlayerStats)		( const edict_t *pClient, int *ping, int *packet_loss );

	void		(*pfnAddServerCommand)		( char *cmd_name, void (*function) (void) );

	qboolean	(*pfnVoice_GetClientListening)(int iReceiver, int iSender);
	qboolean	(*pfnVoice_SetClientListening)(int iReceiver, int iSender, qboolean bListen);

	const char *(*pfnGetPlayerAuthId)		( edict_t *e );

	
	sequenceEntry_s*	(*pfnSequenceGet)			( const char* fileName, const char* entryName );
	sentenceEntry_s*	(*pfnSequencePickSentence)	( const char* groupName, int pickMethod, int *picked );

	int			(*pfnGetFileSize)			( char *filename );

	unsigned int (*pfnGetApproxWavePlayLen) (const char *filepath);
	int			(*pfnIsCareerMatch)			( void );

	int			(*pfnGetLocalizedStringLength)(const char *label);

	void (*pfnRegisterTutorMessageShown)(int mid);
	int (*pfnGetTimesTutorMessageShown)(int mid);
	void (*ProcessTutorMessageDecayBuffer)(int *buffer, int bufferLength);
	void (*ConstructTutorMessageDecayBuffer)(int *buffer, int bufferLength);
	void (*ResetTutorMessageDecayData)( void );

	void (*pfnQueryClientCvarValue)( const edict_t *player, const char *cvarName );
	void (*pfnQueryClientCvarValue2)( const edict_t *player, const char *cvarName, int requestID );
	int (*pfnCheckParm)( const char *pchCmdLineToken, char **ppnext );

	edict_t*	(*pfnPEntityOfEntIndexAllEntities)		(int iEntIndex);
} enginefuncs_t;



typedef struct KeyValueData_s
{
	char	*szClassName;
	char	*szKeyName;
	char	*szValue;
	int32	fHandled;
} KeyValueData;


typedef struct
{
	char		mapName[ 32 ];
	char		landmarkName[ 32 ];
	edict_t	*pentLandmark;
	vec3_t		vecLandmarkOrigin;
} LEVELLIST;
#define MAX_LEVEL_CONNECTIONS	16

typedef struct 
{
	int			id;
	edict_t	*pent;

	int			location;
	int			size;
	int			flags;
	string_t	classname;

} ENTITYTABLE;

#define FENTTABLE_PLAYER		0x80000000
#define FENTTABLE_REMOVED		0x40000000
#define FENTTABLE_MOVEABLE		0x20000000
#define FENTTABLE_GLOBAL		0x10000000

typedef struct saverestore_s SAVERESTOREDATA;

#ifdef _WIN32
typedef 
#endif
struct saverestore_s
{
	char		*pBaseData;
	char		*pCurrentData;
	int			size;
	int			bufferSize;
	int			tokenSize;
	int			tokenCount;
	char		**pTokens;
	int			currentIndex;
	int			tableCount;
	int			connectionCount;
	ENTITYTABLE	*pTable;
	LEVELLIST	levelList[ MAX_LEVEL_CONNECTIONS ];

	int			fUseLandmark;
	char		szLandmarkName[20];
	vec3_t		vecLandmarkOffset;
	float		time;
	char		szCurrentMapName[32];

} 
#ifdef _WIN32
SAVERESTOREDATA 
#endif
;

typedef enum _fieldtypes
{
	FIELD_FLOAT = 0,
	FIELD_STRING,
	FIELD_ENTITY,
	FIELD_CLASSPTR,
	FIELD_EHANDLE,
	FIELD_EVARS,
	FIELD_EDICT,
	FIELD_VECTOR,
	FIELD_POSITION_VECTOR,
	FIELD_POINTER,
	FIELD_INTEGER,
	FIELD_FUNCTION,
	FIELD_BOOLEAN,
	FIELD_SHORT,
	FIELD_CHARACTER,
	FIELD_TIME,
	FIELD_MODELNAME,
	FIELD_SOUNDNAME,

	FIELD_TYPECOUNT,
} FIELDTYPE;

#if !defined(offsetof)  && !defined(GNUC)
#define offsetof(s,m)	(size_t)&(((s *)0)->m)
#endif

#define _FIELD(type,name,fieldtype,count,flags)		{ fieldtype, #name, offsetof(type, name), count, flags }
#define DEFINE_FIELD(type,name,fieldtype)			_FIELD(type, name, fieldtype, 1, 0)
#define DEFINE_ARRAY(type,name,fieldtype,count)		_FIELD(type, name, fieldtype, count, 0)
#define DEFINE_ENTITY_FIELD(name,fieldtype)			_FIELD(entvars_t, name, fieldtype, 1, 0 )
#define DEFINE_ENTITY_GLOBAL_FIELD(name,fieldtype)	_FIELD(entvars_t, name, fieldtype, 1, FTYPEDESC_GLOBAL )
#define DEFINE_GLOBAL_FIELD(type,name,fieldtype)	_FIELD(type, name, fieldtype, 1, FTYPEDESC_GLOBAL )


#define FTYPEDESC_GLOBAL			0x0001

typedef struct 
{
	FIELDTYPE		fieldType;
	char			*fieldName;
	int				fieldOffset;
	short			fieldSize;
	short			flags;
} TYPEDESCRIPTION;

#ifndef ARRAYSIZE
#define ARRAYSIZE(p)		(sizeof(p)/sizeof(p[0]))
#endif


typedef struct 
{
	void			(*pfnGameInit)			( void );				
	int				(*pfnSpawn)				( edict_t *pent );
	void			(*pfnThink)				( edict_t *pent );
	void			(*pfnUse)				( edict_t *pentUsed, edict_t *pentOther );
	void			(*pfnTouch)				( edict_t *pentTouched, edict_t *pentOther );
	void			(*pfnBlocked)			( edict_t *pentBlocked, edict_t *pentOther );
	void			(*pfnKeyValue)			( edict_t *pentKeyvalue, KeyValueData *pkvd );
	void			(*pfnSave)				( edict_t *pent, SAVERESTOREDATA *pSaveData );
	int 			(*pfnRestore)			( edict_t *pent, SAVERESTOREDATA *pSaveData, int globalEntity );
	void			(*pfnSetAbsBox)			( edict_t *pent );

	void			(*pfnSaveWriteFields)	( SAVERESTOREDATA *, const char *, void *, TYPEDESCRIPTION *, int );
	void			(*pfnSaveReadFields)	( SAVERESTOREDATA *, const char *, void *, TYPEDESCRIPTION *, int );

	void			(*pfnSaveGlobalState)		( SAVERESTOREDATA * );
	void			(*pfnRestoreGlobalState)	( SAVERESTOREDATA * );
	void			(*pfnResetGlobalState)		( void );

	qboolean		(*pfnClientConnect)		( edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[ 128 ] );
	
	void			(*pfnClientDisconnect)	( edict_t *pEntity );
	void			(*pfnClientKill)		( edict_t *pEntity );
	void			(*pfnClientPutInServer)	( edict_t *pEntity );
	void			(*pfnClientCommand)		( edict_t *pEntity );
	void			(*pfnClientUserInfoChanged)( edict_t *pEntity, char *infobuffer );

	void			(*pfnServerActivate)	( edict_t *pEdictList, int edictCount, int clientMax );
	void			(*pfnServerDeactivate)	( void );

	void			(*pfnPlayerPreThink)	( edict_t *pEntity );
	void			(*pfnPlayerPostThink)	( edict_t *pEntity );

	void			(*pfnStartFrame)		( void );
	void			(*pfnParmsNewLevel)		( void );
	void			(*pfnParmsChangeLevel)	( void );

	const char     *(*pfnGetGameDescription)( void );     

	void            (*pfnPlayerCustomization) ( edict_t *pEntity, customization_t *pCustom );  

	void			(*pfnSpectatorConnect)		( edict_t *pEntity );
	void			(*pfnSpectatorDisconnect)	( edict_t *pEntity );
	void			(*pfnSpectatorThink)		( edict_t *pEntity );

	void			(*pfnSys_Error)			( const char *error_string );

	void			(*pfnPM_Move) ( struct playermove_s *ppmove, qboolean server );
	void			(*pfnPM_Init) ( struct playermove_s *ppmove );
	char			(*pfnPM_FindTextureType)( char *name );
	void			(*pfnSetupVisibility)( struct edict_s *pViewEntity, struct edict_s *pClient, unsigned char **pvs, unsigned char **pas );
	void			(*pfnUpdateClientData) ( const struct edict_s *ent, int sendweapons, struct clientdata_s *cd );
	int				(*pfnAddToFullPack)( struct entity_state_s *state, int e, edict_t *ent, edict_t *host, int hostflags, int player, unsigned char *pSet );
	void			(*pfnCreateBaseline) ( int player, int eindex, struct entity_state_s *baseline, struct edict_s *entity, int playermodelindex, vec3_t player_mins, vec3_t player_maxs );
	void			(*pfnRegisterEncoders)	( void );
	int				(*pfnGetWeaponData)		( struct edict_s *player, struct weapon_data_s *info );

	void			(*pfnCmdStart)			( const edict_t *player, const struct usercmd_s *cmd, unsigned int random_seed );
	void			(*pfnCmdEnd)			( const edict_t *player );

	int				(*pfnConnectionlessPacket )	( const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size );

	int				(*pfnGetHullBounds)	( int hullnumber, float *mins, float *maxs );

	void			(*pfnCreateInstancedBaselines) ( void );

	int				(*pfnInconsistentFile)( const struct edict_s *player, const char *filename, char *disconnect_message );

	int				(*pfnAllowLagCompensation)( void );
} DLL_FUNCTIONS;

extern DLL_FUNCTIONS		gEntityInterface;

#define NEW_DLL_FUNCTIONS_VERSION	1

typedef struct
{
	void			(*pfnOnFreeEntPrivateData)(edict_t *pEnt);
	void			(*pfnGameShutdown)(void);
	int				(*pfnShouldCollide)( edict_t *pentTouched, edict_t *pentOther );
	void			(*pfnCvarValue)( const edict_t *pEnt, const char *value );
	void			(*pfnCvarValue2)( const edict_t *pEnt, int requestID, const char *cvarName, const char *value );
} NEW_DLL_FUNCTIONS;
typedef int	(*NEW_DLL_FUNCTIONS_FN)( NEW_DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion );

extern NEW_DLL_FUNCTIONS	gNewDLLFunctions;

typedef int	(*APIFUNCTION)( DLL_FUNCTIONS *pFunctionTable, int interfaceVersion );
typedef int	(*APIFUNCTION2)( DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion );

#endif EIFACE_H