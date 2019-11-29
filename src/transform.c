#include "fdf.h"

t_array fdf_transform(s_fdf_map* map)
{
	t_array       result = NEW_ARRAY(s_point3_int);
	s_point3_int* iterator = ARRAY_ITERATOR(&(map->points));
	t_3Dpoint     point;
	s_point3_int  screen_point;

	fta_reserve(&result, map->points.size);
	while ((void*)++iterator < ARRAY_END(&(map->points)))
	{
		point = MAKE_POINT(float, iterator->x, -iterator->y, iterator->z);

		point.x -= map->dim.x / 2;
		point.y += map->dim.y / 2;

		/* ... */

		screen_point = MAKE_POINT(int, point.x, point.y, iterator->z);
		fta_append(&result, &screen_point, 1);
	}
	return result;
}
