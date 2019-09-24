#include "fdf.h"
#include <mlx.h>

bool add_window(s_env* env, t_dimension dim, const char* name)
{
	s_window win;

	win.mlx_win = mlx_new_window(env->mlx, dim.x, dim.y, name);
	win.mlx_img = mlx_new_image(env->mlx, dim.x, dim.y);
	if (win.mlx_win == NULL || win.mlx_img == NULL)
		return false;
	win.pixels = mlx_get_data_addr(win.mlx_img, &(win.bit_per_pixel),
								   &(win.line_size), &(win.endian));
	win.dim = dim;
	fta_append(&(env->windows), &win, 1);
	return true;
}

void free_window(s_window* win, void* mlx)
{
	mlx_destroy_image(mlx, win->mlx_img);
	mlx_destroy_window(mlx, win->mlx_win);
}
