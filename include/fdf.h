#pragma once

#include "colors.h"
#include "mlx_wrapper.h"

#include <ft_array.h>

#define SET_FLOAT_PRECISION(T)	  \
	typedef T                 t_real; \
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

#define DEFAULT_FDF_PALLETTE (struct fdf_pallette){RGB(255,255,255), RGB(140,140,140), RGB(140,200,110), RGB(130,180,230), RGB(50,50,150)}

#define FDF_HOOKS (struct hooks){fdf_expose, fdf_repaint, fdf_key_press, NULL, NULL, NULL, NULL}

#define NEW_FDF_MAP (t_fdf_map){NEW_ARRAY(t_point3_int), MAKE_POINT(unsigned,0,0), 0, 0}
#define NEW_FDF_ENV (t_fdf_env){NEW_WINDOW, NEW_FDF_MAP, DEFAULT_FDF_PALLETTE, {0,0,0}, {0,0}, 1}

void fdf_init(t_fdf_env* env);

void fdf_free(t_fdf_env* env);

int  fdf_start(const char* program_name, const char* filename, t_dimension dim, const char* title);
int  headless(const char* program_name, const char* input_file_name, t_dimension dim, const char* output_file_name);

/*
** FDF::parse
** -
** Loads the specified file into a map.
** In case of failure the map will have 0 element.
*/
t_fdf_map fdf_parse(const char* filename);

/*
** FDF::transform
** -
** The ouput format is an array of 3D integer points,
** whose first two coordinates correspond to a pixel,
** and the last is a color.
*/
t_array fdf_transform(t_fdf_env* env);

/* Hook called to refresh the contents of the image, implies fdf_expose */
int fdf_repaint(t_fdf_env* env);

/* Hook called to reapply the image on the window */
int fdf_expose(t_window* win);

/* Hook called to handle a keyboard input */
int fdf_key_press(int key, t_fdf_env* env);

void fdf_draw_gradient(t_fdf_env* env, t_point3_int from, t_point3_int to);
