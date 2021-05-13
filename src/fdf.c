#include "fdf.h"

#include <errno.h>
#include <ft_printf.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>

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

static void free_fdf_array(t_array* self)
{
	fta_clearf(self, (void*)fdf_free);
}

int fdf_start(const char* program_name, const char* filename, t_dimension dim, const char* title)
{
	void*     mlx;
	t_array   windows __attribute__((cleanup(free_fdf_array))) = NEW_ARRAY(t_fdf_env);
	t_fdf_env fdf = NEW_FDF_ENV;

	errno   = 0;
	fdf.map = fdf_parse(filename);
	if (fdf.map.points.size == 0)
	{
		perror(program_name);
		return 3;
	}
	if ((mlx = mlx_init()) == NULL
	    || !make_window(&fdf.win, mlx, dim, title, FDF_HOOKS)
	    || fta_append(&windows, &fdf, 1) != 0)
	{
		ft_dprintf(2, "%s: MLX initialization failure\n", program_name);
		return 4;
	}
	mlx_do_key_autorepeaton(mlx);
	fdf_init(&fdf);
	fdf_repaint(&fdf);
	fdf_expose(&fdf.win);
	mlx_loop(mlx);
	return 0;
}
