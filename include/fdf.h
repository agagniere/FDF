#pragma once

#include "colors.h"
#include "fdf_errors.h"
#include "mlx_wrapper.h"

#include <ft_array.h>

#define SET_FLOAT_PRECISION(T)           \
	typedef T                 t_real;    \
	typedef struct point2_##T t_complex; \
	typedef struct point3_##T t_3Dpoint

SET_FLOAT_PRECISION(float);

typedef struct fdf_map t_fdf_map;
typedef struct fdf_env t_fdf_env;

struct fdf_map
{
	t_array     points;
	t_dimension dim;
	int         z_max;
	int         z_min;
};

struct fdf_pallette
{
	t_color_rgb background;
	t_color_rgb top;
	t_color_rgb bottom;
	t_color_rgb subzero_top;
	t_color_rgb subzero_bottom;
};

struct fdf_env
{
	t_window            win;
	t_fdf_map           map;
	struct fdf_pallette pallette;
	t_3Dpoint           rotation;
	t_point2_int        offset;
	float               zoom;
};

#define DEFAULT_FDF_PALLETTE                  \
	(struct fdf_pallette)                     \
	{                                         \
		.background     = RGB(255, 255, 255), \
		.top            = RGB(140, 140, 140), \
		.bottom         = RGB(140, 200, 110), \
		.subzero_top    = RGB(130, 180, 230), \
		.subzero_bottom = RGB(50,   50, 150)  \
	}

#define FDF_HOOKS                   \
	(struct hooks)                  \
	{                               \
		.expose    = fdf_expose,    \
		.repaint   = fdf_repaint,   \
		.key_press = fdf_key_press, \
		NULL, NULL, NULL, NULL      \
	}

#define NEW_FDF_MAP                           \
	(struct fdf_map)                          \
	{                                         \
		.points = NEW_ARRAY(t_point3_int),    \
		.dim    = MAKE_POINT(unsigned, 0, 0), \
		.z_max  = 0,                          \
		.z_min  = 0                           \
	}

#define NEW_FDF_ENV                       \
	(struct fdf_env)                      \
	{                                     \
		.win      = NEW_WINDOW,           \
		.map      = NEW_FDF_MAP,          \
		.pallette = DEFAULT_FDF_PALLETTE, \
		.rotation = {0, 0, 0},            \
		.offset   = {0, 0},               \
		.zoom     = 1                     \
	}

void        fdf_init(t_fdf_env* env);
void        fdf_free(t_fdf_env* env);

t_fdf_error fdf_start(const char* filename, t_dimension dim, const char* title);
t_fdf_error headless(const char* input_file_name, t_dimension dim, const char* output_file_name, int benchmark_iterations);

/*
** FDF::parse
** -
** Loads the specified file into the map.
*/
t_fdf_error fdf_parse(const char* filename, t_fdf_map* out_map);

/*
** FDF::transform
** -
** The ouput format is an array of 3D integer points,
** whose first two coordinates correspond to a pixel,
** and the last is a color.
** -
** Its returned array MUST BE FREED with fta_clear
*/
t_array fdf_transform(t_fdf_env* env);

/* Hook called to refresh the contents of the image, implies fdf_expose */
int fdf_repaint(t_fdf_env* env);

/* Hook called to reapply the image on the window */
int fdf_expose(t_window* win);

/* Hook called to handle a keyboard input */
int fdf_key_press(int key, t_fdf_env* env);

int fdf_draw_gradient(t_fdf_env* env, t_point3_int from, t_point3_int to);
