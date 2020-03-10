#include "fdf.h"
#include "mlx_wrapper.h"
#include "keys.h"

#include <mlx.h>
#include <ft_printf.h>
#include <stdlib.h>
#include <time.h>

int fdf_expose(s_window* win)
{
	mlx_put_image_to_window(win->mlx_ptr, win->mlx_win, win->mlx_img, 0, 0);
	return 0;
}

# define GET(N) ARRAY_GETL(s_point2_int, &screen_points, N)

int fdf_repaint(s_fdf_env* env)
{
	struct timespec before, after;
	clock_gettime(CLOCK_REALTIME, &before);
	t_array screen_points = fdf_transform(env);
	clock_gettime(CLOCK_REALTIME, &after);
	unsigned i = screen_points.size;

	ft_printf("%lu points in %li seconds and %7u ns\n", i, after.tv_sec - before.tv_sec, after.tv_nsec - before.tv_nsec);
	ft_memset(env->win.pixels, 250 + (250 << 8) + (250 << 16), env->win.line_size * env->win.dim.y);
	while (i --> 1)
	{
		if (i % env->map.dim.x > 0)
			draw_line(&env->win, GET(i), GET(i - 1), 200 + (200 << 8));
		if (i / env->map.dim.x > 0)
			draw_line(&env->win, GET(i), GET(i - env->map.dim.x), 200 + (200 << 16));
	}
	fdf_expose(&env->win);
	return 0;
}

int fdf_key_press(int key, s_fdf_env* env)
{
	switch (key)
	{
	case KEY_Equal:
	case KEY_KeypadPlus:   env->zoom *= 1.5;        break;
	case KEY_Minus:
	case KEY_KeypadMinus:  env->zoom /= 1.5;        break;
	case KEY_LeftArrow:    env->rotation.z -= 0.2;  break;
	case KEY_RightArrow:   env->rotation.z += 0.2;  break;
	case KEY_LeftBracket:  env->rotation.y += 0.2;  break;
	case KEY_RightBracket: env->rotation.y -= 0.2;  break;
	case KEY_UpArrow:      env->rotation.x += 0.2;  break;
	case KEY_DownArrow:    env->rotation.x -= 0.2;  break;
	case KEY_Q:            exit(0);
	default:               return 0;
	}
	fdf_repaint(env);
	return 0;
}
