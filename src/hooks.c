#include "mlx_wrapper.h"
#include <mlx.h>

int fdf_expose(s_window* win)
{
	mlx_put_image_to_window(win->mlx_ptr, win->mlx_win, win->mlx_img, 0, 0);
	return 0;
}

int fdf_repaint(s_window* win)
{
	return 0;
}

int fdf_key_press(int key, s_window* win)
{
	return 0;
}
