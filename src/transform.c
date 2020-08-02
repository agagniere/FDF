#include "fdf.h"

#include <math.h>

typedef t_real t_matrix;

void add_rotation(t_matrix* m, t_real angle, int axe)
{
	const t_real s = sinf(angle);
	const t_real c = cosf(angle);
	t_matrix b[9] = { c, -s,  s,
	                  s,  c, -s,
	                 -s,  s,  c};
	t_matrix r[9];
	int i = 3;

	while (i --> 0)
		b[3 * axe + i] = (b[3 * i + axe] = 0);
	b[3 * axe + axe] = 1;
	i = 9;
	while (i --> 0)
	{
		r[i]  = 0;
		int x = i % 3;
		int y = i / 3;
		int j = 3;
		while (j --> 0)
			r[i] += m[3*j+x] * b[3*y+j];
	}
	ft_memcpy(m, r, sizeof(r));
}

t_array fdf_transform(t_fdf_env* env)
{
	t_array       result   = NEW_ARRAY(t_point3_int);
	t_point3_int* iterator = ARRAY_ITERATOR(&env->map.points);
	t_matrix      t[3 * 3] = {env->zoom,0,0, 0,env->zoom,0, 0,0,env->zoom};

	add_rotation(t, env->rotation.z, 2);
	add_rotation(t, env->rotation.y, 1);
	add_rotation(t, env->rotation.x, 0);
	fta_reserve(&result, env->map.points.size);
	while ((void*)++iterator < ARRAY_END(&env->map.points))
	{
		t_3Dpoint point = MAKE_POINT(float, iterator->x, iterator->y, iterator->z);
		t_real    x = point.x - env->map.dim.x / 2;
		t_real    y = point.y - env->map.dim.y / 2;

		point.x = x * t[0] + y * t[1] + point.z * t[2];
		point.y = x * t[3] + y * t[4] + point.z * t[5];
		point.z = x * t[6] + y * t[7] + point.z * t[8];
		fta_append(&result, (t_point3_int[]){{env->offset.x + point.x, env->offset.y + point.y, iterator->z}}, 1);
	}
	return result;
}

t_array fdf_transform_simplistic(t_fdf_env* env)
{
	t_array       result   = NEW_ARRAY(t_point3_int);
	t_point3_int* iterator = ARRAY_ITERATOR(&env->map.points);
	t_3Dpoint     point;
	t_point3_int  screen_point;

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

		f =       point.x * cos(env->rotation.y) + point.z * sin(env->rotation.y);
		point.z =-point.x * sin(env->rotation.y) + point.z * cos(env->rotation.y);
		point.x = f;

		point.x *= env->zoom;
		point.y *= env->zoom;
		point.z *= env->zoom;

		screen_point = MAKE_POINT(int, env->offset.x + point.x, env->offset.y + point.y, iterator->z);
		fta_append(&result, &screen_point, 1);
	}
	return result;
}
