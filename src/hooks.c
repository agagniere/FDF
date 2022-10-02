#include "fdf.h"
#include "keys.h"
#include "mlx_wrapper.h"

#include <ft_printf.h>
#include <mlx.h>
#include <stdlib.h>
#include <time.h>

#define CLOCK CLOCK_MONOTONIC_RAW
#define time_diff(A, B) ((B.tv_sec - A.tv_sec) * 1000000000 + B.tv_nsec - A.tv_nsec)

#define NAIVE 2

#if !defined(DRAWING_ALGO)
# define GET(N) ARRAY_GETL(t_point3_int, &screen_points, N)
# define draw fdf_draw_gradient
#elif DRAWING_ALGO == NAIVE
# define GET(N) ARRAY_GETL(t_point2_int, &screen_points, N)
# define draw(env, a, b) draw_line((t_window*)env, a, b, (150 << 8) + 200)
#else
#error Unknown drawing algorithm DRAWING_ALGO
#endif

int fdf_expose(t_window* win)
{
	mlx_put_image_to_window(win->mlx_ptr, win->mlx_win, win->mlx_img, 0, 0);
	return 0;
}

int fdf_repaint(t_fdf_env* env)
{
	struct timespec before, after;
	clock_gettime(CLOCK, &before);
	t_array screen_points __attribute__((cleanup(fta_clear))) = fdf_transform(env);
	clock_gettime(CLOCK, &after);
	unsigned i = screen_points.size;
	unsigned lines = 0;

	ft_printf("%u %lu ", i, time_diff(before, after));
	ft_memset(env->win.pixels, env->pallette.background.color, env->win.line_size * env->win.dim.y);
	clock_gettime(CLOCK, &before);
	while (i --> 1)
	{
		if (i % env->map.dim.x > 0)
			lines += draw(env, GET(i), GET(i - 1));
		if (i >= env->map.dim.x)
			lines += draw(env, GET(i), GET(i - env->map.dim.x));
		if (i % env->map.dim.x > 0 && i >= env->map.dim.x)
			lines += draw(env, GET(i - 1), GET(i - env->map.dim.x));
	}
	clock_gettime(CLOCK, &after);
	ft_printf("%u %lu\n", lines, time_diff(before, after));
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
	case KEY_Delete:       fdf_init(env);           break;
	case KEY_W:            env->offset.y -= env->win.dim.y / 10; break;
	case KEY_S:            env->offset.y += env->win.dim.y / 10; break;
	case KEY_A:            env->offset.x -= env->win.dim.x / 10; break;
	case KEY_D:            env->offset.x += env->win.dim.x / 10; break;
	case KEY_Q:            exit(0);
	default:               return 0;
	}
	fdf_repaint(env);
	fdf_expose(&env->win);
	return 0;
}
