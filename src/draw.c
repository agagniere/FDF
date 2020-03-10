#include "mlx_wrapper.h"

#include <ft_prepro.h>
#include <ft_printf.h>
#include <stdbool.h>

static bool is_in_frame(s_window* win, unsigned x, unsigned y)
{
	return x < win->dim.x && y < win->dim.y;
}

void set_pixel(s_window* win, unsigned x, unsigned y, int color)
{
	int* whole_pixels = (int*)win->pixels;

	if (is_in_frame(win, x, y))
		whole_pixels[win->dim.x * y + x] = color;
}

void draw_line(s_window* win, s_point2_int from, s_point2_int to, int color)
{
	s_point2_int diff          = MAKE_POINT(int, to.x - from.x, to.y - from.y);
	bool         is_horizontal = ABS(diff.x) > ABS(diff.y);
	int          max           = is_horizontal ? diff.x : diff.y;
	int          way           = (max > 0) * 2 - 1;
	int          i             = 0;

	if (!is_in_frame(win, from.x, from.y) && !is_in_frame(win, to.x, to.y))
	{
		ft_dprintf(2, "%s aborted because both points are off bounds.\n", __FUNCTION__);
		return;
	}
	while (i != max)
	{
		if (is_horizontal)
			set_pixel(win, from.x + i, from.y + diff.y * i / diff.x, color);
		else
			set_pixel(win, from.x + diff.x * i / diff.y, from.y + i, color);
		i += way;
	}
	set_pixel(win, to.x, to.y, color);
}
