#include "fdf.h"
#include <mlx.h>
#include <strings.h>

bool make_window(void* mlx, t_dimension dim, const char* name, s_hooks hooks, s_window* dest)
{
	dest->dim = dim;
	dest->hooks = hooks;
	dest->mlx_ptr = mlx;
	dest->mlx_img = mlx_new_image(mlx, dim.x, dim.y);
	dest->mlx_win = mlx_new_window(mlx, dim.x, dim.y, (char*)name);
	if (dest->mlx_win == NULL || dest->mlx_img == NULL)
		return false;
	dest->pixels = (uint8_t*)mlx_get_data_addr(dest->mlx_img, &(dest->bit_per_pixel),
											   &(dest->line_size), &(dest->endian));
	if (hooks.expose)
		mlx_expose_hook(dest->mlx_win, hooks.expose, dest);
	if (hooks.key_press)
		mlx_key_hook(dest->mlx_win, hooks.key_press, dest);
	return true;
}

void free_window(s_window* win)
{
	mlx_destroy_image(win->mlx_ptr, win->mlx_img);
	mlx_destroy_window(win->mlx_ptr, win->mlx_win);
	bzero(win, sizeof(win));
}
