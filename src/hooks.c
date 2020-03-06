#include "fdf.h"
#include "mlx_wrapper.h"
#include "keys.h"

#include <mlx.h>
#include <ft_printf.h>
#include <stdlib.h>

int fdf_expose(s_window* win)
{
	ft_printf("Hook %s\n", __FUNCTION__);
	mlx_put_image_to_window(win->mlx_ptr, win->mlx_win, win->mlx_img, 0, 0);
	return 0;
}

# define GET(N) ARRAY_GETL(s_point2_int, screen_points, N)

int fdf_repaint(s_window* win)
{
	s_fdf_map* map = (void*)(win + 1);
	t_array screen_points[1] = {fdf_transform(map)};

	ft_printf("Hook %s\n", __FUNCTION__);
	ft_printf("%lu points\n", screen_points->size);

	unsigned i = screen_points->size;
	while (i --> 1)
	{
		if (i % map->dim.x > 0)
			draw_line(win, GET(i), GET(i - 1), 255);
		if (i / map->dim.x > 0)
			draw_line(win, GET(i), GET(i - map->dim.x), 255);
	}
	fdf_expose(win);
	return 0;
}

int fdf_key_press(int key, s_window* win)
{
	(void)win;
	ft_printf("Pressed %i\n", key);
	if (key == KEY_Q)
		exit(0);
	fdf_repaint(win);
	return 0;
}
