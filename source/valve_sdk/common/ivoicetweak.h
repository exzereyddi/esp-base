
#ifndef IVOICETWEAK_H
#define IVOICETWEAK_H
#ifdef _WIN32
#pragma once
#endif

typedef enum
{
	MicrophoneVolume=0,
	OtherSpeakerScale,
	MicBoost,
} VoiceTweakControl;


typedef struct IVoiceTweak_s
{
	int				(*StartVoiceTweakMode)();
	void			(*EndVoiceTweakMode)();
	
	void			(*SetControlFloat)(VoiceTweakControl iControl, float value);
	float			(*GetControlFloat)(VoiceTweakControl iControl);

    int             (*GetSpeakingVolume)();
} IVoiceTweak;


#endif