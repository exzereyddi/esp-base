
#if !defined( SCREENFADEH )
#define SCREENFADEH
#ifdef _WIN32
#pragma once
#endif

typedef struct screenfade_s
{
	float		fadeSpeed;
	float		fadeEnd;
	float		fadeTotalEnd;
	float		fadeReset;
	byte		fader, fadeg, fadeb, fadealpha;
	int			fadeFlags;
} screenfade_t;

#endif