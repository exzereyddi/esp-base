#pragma once

typedef unsigned char uint8;
typedef signed char int8;

typedef unsigned short uint16;
typedef signed short int16;

typedef unsigned int uint32;
typedef signed int int32;

typedef unsigned long long uint64;
typedef signed long long int64;

typedef float float32;
typedef double float64;

typedef unsigned int uintptr;

#ifdef _WIN32
typedef wchar_t uchar16;
typedef unsigned int uchar32;
#endif