#ifndef _INCLUDE_SEQUENCE_H_
#define _INCLUDE_SEQUENCE_H_


#ifndef _DEF_BYTE_
typedef unsigned char byte;
#endif

typedef struct client_textmessage_s
{
	int		effect;
	byte	r1, g1, b1, a1;
	byte	r2, g2, b2, a2;
	float	x;
	float	y;
	float	fadein;
	float	fadeout;
	float	holdtime;
	float	fxtime;
	const char *pName;
	const char *pMessage;
} client_textmessage_t;


enum sequenceModifierBits
{
	SEQUENCE_MODIFIER_EFFECT_BIT		= (1 << 1),
	SEQUENCE_MODIFIER_POSITION_BIT		= (1 << 2),
	SEQUENCE_MODIFIER_COLOR_BIT			= (1 << 3),
	SEQUENCE_MODIFIER_COLOR2_BIT		= (1 << 4),
	SEQUENCE_MODIFIER_FADEIN_BIT		= (1 << 5),
	SEQUENCE_MODIFIER_FADEOUT_BIT		= (1 << 6),
	SEQUENCE_MODIFIER_HOLDTIME_BIT		= (1 << 7),
	SEQUENCE_MODIFIER_FXTIME_BIT		= (1 << 8),
	SEQUENCE_MODIFIER_SPEAKER_BIT		= (1 << 9),
	SEQUENCE_MODIFIER_LISTENER_BIT		= (1 << 10),
	SEQUENCE_MODIFIER_TEXTCHANNEL_BIT	= (1 << 11),
};
typedef enum sequenceModifierBits sequenceModifierBits_e ;


enum sequenceCommandEnum_
{
	SEQUENCE_COMMAND_ERROR = -1,
	SEQUENCE_COMMAND_PAUSE = 0,
	SEQUENCE_COMMAND_FIRETARGETS,
	SEQUENCE_COMMAND_KILLTARGETS,
	SEQUENCE_COMMAND_TEXT,
	SEQUENCE_COMMAND_SOUND,
	SEQUENCE_COMMAND_GOSUB,
	SEQUENCE_COMMAND_SENTENCE,
	SEQUENCE_COMMAND_REPEAT,
	SEQUENCE_COMMAND_SETDEFAULTS,
	SEQUENCE_COMMAND_MODIFIER,
	SEQUENCE_COMMAND_POSTMODIFIER,
	SEQUENCE_COMMAND_NOOP,

	SEQUENCE_MODIFIER_EFFECT,
	SEQUENCE_MODIFIER_POSITION,
	SEQUENCE_MODIFIER_COLOR,
	SEQUENCE_MODIFIER_COLOR2,
	SEQUENCE_MODIFIER_FADEIN,
	SEQUENCE_MODIFIER_FADEOUT,
	SEQUENCE_MODIFIER_HOLDTIME,
	SEQUENCE_MODIFIER_FXTIME,
	SEQUENCE_MODIFIER_SPEAKER,
	SEQUENCE_MODIFIER_LISTENER,
	SEQUENCE_MODIFIER_TEXTCHANNEL,
};
typedef enum sequenceCommandEnum_ sequenceCommandEnum_e;


enum sequenceCommandType_
{
	SEQUENCE_TYPE_COMMAND,
	SEQUENCE_TYPE_MODIFIER,
};
typedef enum sequenceCommandType_ sequenceCommandType_e;


typedef struct sequenceCommandMapping_ sequenceCommandMapping_s;
struct sequenceCommandMapping_
{
	sequenceCommandEnum_e	commandEnum;
	const char*				commandName;
	sequenceCommandType_e	commandType;
};


typedef struct sequenceCommandLine_ sequenceCommandLine_s;
struct sequenceCommandLine_
{
	int						commandType;
	client_textmessage_t	clientMessage;
	char*					speakerName;
	char*					listenerName;
	char*					soundFileName;
	char*					sentenceName;
	char*					fireTargetNames;
	char*					killTargetNames;
	float					delay;
	int						repeatCount;
	int						textChannel;
	int						modifierBitField;
	sequenceCommandLine_s*	nextCommandLine;
};


typedef struct sequenceEntry_ sequenceEntry_s;
struct sequenceEntry_
{
	char*					fileName;
	char*					entryName;
	sequenceCommandLine_s*	firstCommand;
	sequenceEntry_s*		nextEntry;
	qboolean				isGlobal;
};



typedef struct sentenceEntry_ sentenceEntry_s;
struct sentenceEntry_
{
	char*					data;
	sentenceEntry_s*		nextEntry;
	qboolean				isGlobal;
	unsigned int			index;
};

typedef struct sentenceGroupEntry_ sentenceGroupEntry_s;
struct sentenceGroupEntry_
{
	char*					groupName;
	unsigned int			numSentences;
	sentenceEntry_s*		firstSentence;
	sentenceGroupEntry_s*	nextEntry;
};

sequenceEntry_s* SequenceGet( const char* fileName, const char* entryName );
void Sequence_ParseFile( const char* fileName, qboolean isGlobal );
void Sequence_OnLevelLoad( const char* mapName );
sentenceEntry_s* SequencePickSentence( const char *groupName, int pickMethod, int *picked );

#endif