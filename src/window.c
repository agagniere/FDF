#include "fdf.h"
#include <mlx.h>
#include <strings.h>

s_window make_window(void* mlx, t_dimension dim, const char* name, s_hooks hooks)
{
	s_window win;

	win.dim = dim;
	win.hooks = hooks;
	win.mlx_ptr = mlx;
	win.mlx_img = mlx_new_image(mlx, dim.x, dim.y);
	win.mlx_win = mlx_new_window(mlx, dim.x, dim.y, (char*)name);
	if (win.mlx_win != NULL && win.mlx_img != NULL)
		win.pixels = (uint8_t*)mlx_get_data_addr(win.mlx_img, &(win.bit_per_pixel),
												 &(win.line_size), &(win.endian));
	return win;
}

void free_window(s_window* win)
{
	mlx_destroy_image(win->mlx_ptr, win->mlx_img);
	mlx_destroy_window(win->mlx_ptr, win->mlx_win);
	bzero(win, sizeof(win));
}
