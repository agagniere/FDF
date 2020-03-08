#include "fdf.h"

#include <math.h>

t_array fdf_transform(s_fdf_env* env)
{
	t_array       result = NEW_ARRAY(s_point3_int);
	s_point3_int* iterator = ARRAY_ITERATOR(&env->map.points);
	t_3Dpoint     point;
	s_point3_int  screen_point;

	fta_reserve(&result, env->map.points.size);
	while ((void*)++iterator < ARRAY_END(&env->map.points))
	{
		point = MAKE_POINT(float, iterator->x, iterator->y, iterator->z);

		point.x -= env->map.dim.x / 2;
		point.y -= env->map.dim.y / 2;

		float f = point.x * cos(env->rotation.z) - point.y * sin(env->rotation.z);
		point.y = point.x * sin(env->rotation.z) + point.y * cos(env->rotation.z);
		point.x = f;

		f =       point.y * cos(env->rotation.x) - point.z * sin(env->rotation.x);
		point.z = point.y * sin(env->rotation.x) + point.z * cos(env->rotation.x);
		point.y = f;

		f =       point.x * cos(env->rotation.y) - point.z * sin(env->rotation.y);
		point.z = point.x * sin(env->rotation.y) + point.z * cos(env->rotation.y);
		point.x = f;

		point.x *= env->zoom;
		point.y *= env->zoom;
		point.z *= env->zoom;

		screen_point = MAKE_POINT(int, env->offset.x + point.x, env->offset.y + point.y, iterator->z);
		fta_append(&result, &screen_point, 1);
	}
	return result;
}
