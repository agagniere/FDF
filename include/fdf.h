#pragma once

#include "mlx_wrapper.h"

#include <ft_array.h>

#define SET_FLOAT_PRECISION(T)					 \
	typedef T                 t_real;            \
	typedef struct point2_##T t_complex;		 \
	typedef struct point3_##T t_3Dpoint

SET_FLOAT_PRECISION(float);

t_array parse_fdf(const char* filename);

int fdf_repaint(s_window* win);
int fdf_expose(s_window* win);
int fdf_key_press(s_window* win);

#define FDF_HOOKS (struct hooks){fdf_expose, fdf_repaint, fdf_key_press, NULL, NULL, NULL, NULL}
