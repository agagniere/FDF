#pragma once

#include "mlx_wrapper.h"

#include <ft_array.h>

#define SET_FLOAT_PRECISION(T)					 \
	typedef T                 t_real;            \
	typedef struct point2_##T t_complex;		 \
	typedef struct point3_##T t_3Dpoint

SET_FLOAT_PRECISION(float);

typedef struct fdf_map s_fdf_map;

struct fdf_map
{
	t_array points;
	t_dimension dim;
	int z_max;
	int z_min;
};

#define NEW_FDF_MAP (s_fdf_map){NEW_ARRAY(s_point3_int), MAKE_POINT(unsigned,0,0), 0, 0}

s_fdf_map fdf_parse(const char* filename);
t_array   fdf_transform(s_fdf_map* map);

int fdf_repaint(s_window* win);
int fdf_expose(s_window* win);
int fdf_key_press(int key, s_window* win);

#define FDF_HOOKS (struct hooks){fdf_expose, fdf_repaint, fdf_key_press, NULL, NULL, NULL, NULL}
