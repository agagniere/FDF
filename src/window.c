#include "fdf.h"
#include <mlx.h>
#include <libft.h>

bool make_window(s_window* out, void* mlx, t_dimension dim, const char* name, s_hooks hooks)
{
	out->dim = dim;
	out->hooks = hooks;
	out->mlx_ptr = mlx;
	out->mlx_img = mlx_new_image(mlx, dim.x, dim.y);
	out->mlx_win = mlx_new_window(mlx, dim.x, dim.y, (char*)name);
	if (out->mlx_win == NULL || out->mlx_img == NULL)
		return false;
	out->pixels = (uint8_t*)mlx_get_data_addr(out->mlx_img, &(out->bit_per_pixel),
											  &(out->line_size), &(out->endian));
	if (hooks.expose)
		mlx_expose_hook(out->mlx_win, hooks.expose, out);
	if (hooks.key_press)
		mlx_key_hook(out->mlx_win, hooks.key_press, out);
	return true;
}

void free_window(s_window* win)
{
	mlx_destroy_image(win->mlx_ptr, win->mlx_img);
	mlx_destroy_window(win->mlx_ptr, win->mlx_win);
	ft_bzero(win, sizeof(win));
}
