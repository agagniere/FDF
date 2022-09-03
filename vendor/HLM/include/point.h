#pragma once

#include <ft_prepro/tools.h>

typedef struct point2_unsigned t_dimension;

#define S_POINTS(T)           \
	typedef struct MERGE(point2, T)              \
	{                         \
		T x;                  \
		T y;                  \
	} MERGE(t, point2, T);    \
	typedef struct MERGE(point3, T)             \
	{                         \
		T x;                  \
		T y;                  \
		T z;                  \
	} MERGE(t, point3, T)

S_POINTS(int);
S_POINTS(unsigned);
S_POINTS(float);
S_POINTS(double);

/*
** make_point macro
** -
** Provided the type of coordinates and their value,
** it evaluates as a point of the right dimension and type.
** -
** example:
** MAKE_POINT(int,3,4) -> (s_point2_int){3,4}
** MAKE_POINT(float,0,7,3) -> (s_point3_float){0,7,3}
*/

#define MAKE_POINT(T, ...) (MERGE(t, CAT(point, ARG_COUNT(__VA_ARGS__)), T)){__VA_ARGS__}
