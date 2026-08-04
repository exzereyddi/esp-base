
#if !defined EDICT_H
#define EDICT_H
#ifdef _WIN32
#pragma once
#endif
#define	MAX_ENT_LEAFS	48

#include "progdefs.h"

struct edict_s
{
	qboolean	free;
	int			serialnumber;
	link_t		area;
	
	int			headnode;
	int			num_leafs;
	short		leafnums[MAX_ENT_LEAFS];

	float		freetime;

	void*		pvPrivateData;

	entvars_t	v;

};

#endif