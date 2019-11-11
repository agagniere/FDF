#include "fdf.h"

t_array fdf_transform(s_fdf_map* map)
{
	t_array result = NEW_ARRAY(t_3Dpoint);
	s_point3_int* iterator = ARRAY_ITERATOR(&(map->points));

	fta_reserve(&result, map->points.size);
	while ((void*)++iterator < ARRAY_END(&(map->points)))
	{
		t_3Dpoint point = MAKE_POINT(float, iterator->x, iterator->y, iterator->z);

		iterator->x -= map->dim.x / 2;
		iterator->y += map->dim.y / 2;

		fta_append(&result, &point, 1);
	}
	return result;
}
