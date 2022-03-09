#include "fdf.h"

#include <ft_printf.h>
#include <math.h>
#include <mlx.h>

/*
** A major non-POSIX OS, Android,
** still defines M_PI and others.
*/

void fdf_init(t_fdf_env* env)
{
	const float height = env->map.z_max - env->map.z_min;
	const float diagonal = sqrt(env->map.dim.x * env->map.dim.x + env->map.dim.y * env->map.dim.y);
	const float x = env->win.dim.x / diagonal;
	const float y = env->win.dim.y / diagonal;
	const float z = env->win.dim.y / height;
	const float zoom = MIN(x, y, z);
	const float mid_height_onscreen = zoom * (env->map.z_min + env->map.z_max) / 2;

	env->zoom = zoom;
	env->rotation.z = M_PI_4;
	env->rotation.x = M_PI_4;
	env->offset.x = env->win.dim.x / 2;
	env->offset.y = env->win.dim.y / 2 + mid_height_onscreen / 2;
}

void fdf_free(t_fdf_env* env)
{
	free_window(&env->win);
	fta_clear(&env->map.points);
}

t_fdf_error fdf_start(const char* filename, t_dimension dim, const char* title)
{
	void*       mlx;
	t_fdf_env   fdf __attribute__((cleanup(fdf_free))) = NEW_FDF_ENV;
	t_fdf_error error = fdf_parse(filename, &fdf.map);

	if (FDF_IS_ERROR(error))
		return error;
	if ((mlx = mlx_init()) == NULL)
		return FDF_ERROR_STATIC("X11/Cocoa failed to open display");
	if (!make_window(&fdf.win, mlx, dim, title, FDF_HOOKS))
		return FDF_ERROR_STATIC("Failed to create a window");
	mlx_do_key_autorepeaton(mlx);
	fdf_init(&fdf);
	fdf_repaint(&fdf);
	fdf_expose(&fdf.win);
	mlx_loop(mlx);
	return FDF_NO_ERROR;
}
