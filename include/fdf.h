#pragma once

#include "mlx_wrapper.h"

#include <ft_array.h>

#define SET_FLOAT_PRECISION(T)           \
	typedef T                 t_real;    \
	typedef struct point2_##T t_complex; \
	typedef struct point3_##T t_3Dpoint

SET_FLOAT_PRECISION(float);

typedef struct fdf_map s_fdf_map;
typedef struct fdf_env s_fdf_env;

struct fdf_map
{
	t_array     points;
	t_dimension dim;
	int         z_max;
	int         z_min;
};

struct fdf_env
{
	s_window     win;
	s_fdf_map    map;
	t_3Dpoint    rotation;
	s_point2_int offset;
	float        zoom;
};

#define FDF_HOOKS (struct hooks){fdf_expose, fdf_repaint, fdf_key_press, NULL, NULL, NULL, NULL}

#define NEW_FDF_MAP (s_fdf_map){NEW_ARRAY(s_point3_int), MAKE_POINT(unsigned,0,0), 0, 0}
#define NEW_FDF_ENV (s_fdf_env){NEW_WINDOW, NEW_FDF_MAP, {0,0,0}, {0,0}, 1}

/*
** FDF::parse
** -
** Loads the specified file into a map.
** In case of failure the map will have 0 element.
*/
s_fdf_map fdf_parse(const char* filename);

/*
** FDF::transform
** -
** The ouput format is an array of 3D integer points,
** whose first two coordinates correspond to a pixel,
** and the last is a color.
*/
t_array fdf_transform(s_fdf_env* env);

/* Hook called to refresh the contents of the image, implies fdf_expose */
int fdf_repaint(s_fdf_env* env);

/* Hook called to reapply the image on the window */
int fdf_expose(s_window* win);

int fdf_key_press(int key, s_fdf_env* env);
