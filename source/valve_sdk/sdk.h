#pragma once

#include <Windows.h>

typedef int qboolean;
typedef unsigned char byte;
typedef float vec_t;
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

#define STRING_T_DEFINED
typedef int string_t;

typedef unsigned short word;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#include "common/wrect.h"
#include "common/cdll_dll.h"
#include "engine/custom.h"
#include "common/const.h"
#include "common/com_model.h"
#include "common/cl_entity.h"
#include "common/ref_params.h"
#include "common/triangleapi.h"
#include "common/event_api.h"
#include "common/net_api.h"
#include "common/r_efx.h"
#include "common/demo_api.h"
#include "common/ivoicetweak.h"
#include "common/r_studioint.h"
#include "common/pmtrace.h"
#include "common/entity_state.h"
#include "common/usercmd.h"
#include "engine/cdll_int.h"