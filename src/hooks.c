#include "fdf.h"
#include "keys.h"
#include "mlx_wrapper.h"

#include <ft_printf.h>
#include <mlx.h>
#include <stdlib.h>
#include <time.h>

int fdf_expose(t_window* win)
{
	mlx_put_image_to_window(win->mlx_ptr, win->mlx_win, win->mlx_img, 0, 0);
	return 0;
}

#define GET(N) ARRAY_GETL(t_point3_int, &screen_points, N)

int fdf_repaint(t_fdf_env* env)
{
	struct timespec before, after;
	clock_gettime(CLOCK_REALTIME, &before);
	t_array screen_points = fdf_transform(env);
	clock_gettime(CLOCK_REALTIME, &after);
	unsigned i = screen_points.size;

	ft_printf("%i %lu ", i, after.tv_nsec - before.tv_nsec);
	ft_memset(env->win.pixels, env->pallette.background.color, env->win.line_size * env->win.dim.y);
	clock_gettime(CLOCK_REALTIME, &before);
	while (i --> 1)
	{
		if (i % env->map.dim.x > 0)
			fdf_draw_gradient(env, GET(i), GET(i - 1));
		if (i / env->map.dim.x > 0)
			fdf_draw_gradient(env, GET(i), GET(i - env->map.dim.x));
	}
	clock_gettime(CLOCK_REALTIME, &after);
	ft_printf("%lu\n", after.tv_nsec - before.tv_nsec);
	fta_clear(&screen_points);
	fdf_expose(&env->win);
	return 0;
}

int fdf_key_press(int key, t_fdf_env* env)
{
	switch (key)
	{
	case KEY_Equal:
	case KEY_KeypadPlus:   env->zoom *= 1.5;        break;
	case KEY_Minus:
	case KEY_KeypadMinus:  env->zoom /= 1.5;        break;
	case KEY_LeftArrow:    env->rotation.z += 0.2;  break;
	case KEY_RightArrow:   env->rotation.z -= 0.2;  break;
	case KEY_LeftBracket:  env->rotation.y -= 0.2;  break;
	case KEY_RightBracket: env->rotation.y += 0.2;  break;
	case KEY_UpArrow:      env->rotation.x += 0.2;  break;
	case KEY_DownArrow:    env->rotation.x -= 0.2;  break;
	case KEY_W:            env->offset.y -= env->win.dim.y / 10; break;
	case KEY_S:            env->offset.y += env->win.dim.y / 10; break;
	case KEY_A:            env->offset.x -= env->win.dim.x / 10; break;
	case KEY_D:            env->offset.x += env->win.dim.x / 10; break;
	case KEY_Q:            exit(0);
	default:               return 0;
	}
	fdf_repaint(env);
	return 0;
}
