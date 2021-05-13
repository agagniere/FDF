#include "mlx_wrapper.h"
#include "fdf.h"

#define _lerp(MIN,DELTA,I,I_MAX) ((MIN) + (DELTA) * (I) / (I_MAX))
#define lerp(MIN,MAX,I,I_MAX) _lerp(MIN, (MAX) - (MIN), I, I_MAX)

int fdf_color(t_fdf_env* env, int altitude)
{
	t_color_rgb color_a, color_b;
	t_color_rgb result;
	int max;
	int i = 3;

	if (altitude < 0)
	{
		max = env->map.z_min;
		color_a = env->pallette.subzero_top;
		color_b = env->pallette.subzero_bottom;
	}
	else
	{
		max = env->map.z_max;
		color_a = env->pallette.bottom;
		color_b = env->pallette.top;
	}
	if (max == 0)
		return color_a.color;
	while (i --> 0)
		result.components[i] = lerp(color_a.components[i], color_b.components[i], altitude, max);
	return result.color;
}

void fdf_draw_gradient(t_fdf_env* env, t_point3_int from, t_point3_int to)
{
	t_point3_int diff          = MAKE_POINT(int, to.x - from.x, to.y - from.y, to.z - from.z);
	bool         is_horizontal = ABS(diff.x) > ABS(diff.y);
	int          max           = is_horizontal ? diff.x : diff.y;
	int          way           = (max > 0) * 2 - 1;
	int          i             = 0;

	if (!is_in_frame(&env->win, from.x, from.y) && !is_in_frame(&env->win, to.x, to.y))
		return ;
	while (i != max)
	{
		if (is_horizontal)
			set_pixel(&env->win, from.x + i, _lerp(from.y, diff.y, i, diff.x), fdf_color(env, _lerp(from.z, diff.z, i, diff.x)));
		else
			set_pixel(&env->win, _lerp(from.x, diff.x, i, diff.y), from.y + i, fdf_color(env, _lerp(from.z, diff.z, i, diff.y)));
		i += way;
	}
	set_pixel(&env->win, to.x, to.y, fdf_color(env, to.z));
}
