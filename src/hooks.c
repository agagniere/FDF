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

int fdf_repaint(s_fdf_env* env)
{
	t_array screen_points[1] = {fdf_transform(env)};

	ft_printf("Hook %s\n", __FUNCTION__);
	ft_printf("%lu points\n", screen_points->size);
	ft_memset(env->win.pixels, 250 + (250 << 8) + (250 << 16), env->win.line_size * env->win.dim.y);

	unsigned i = screen_points->size;
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
	ft_printf("Pressed %i\n", key);
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
	case KEY_Q: exit(0);
	default: return 0;
	}
	fdf_repaint(env);
	return 0;
}
