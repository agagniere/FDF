#include "fdf.h"
#include <libft.h>
#include <ft_ctype.h>
#include <get_next_line.h>

#include <stdlib.h>
#include <fcntl.h>

static void parse_fdf_line(const char* line, s_fdf_map* map, int line_nb)
{
	s_point3_int point = MAKE_POINT(int, 0, -line_nb, 0);

	while (ft_isspace(*line))
		line++;
	while (*line != '\0')
	{
		point.z = ft_atoi(line);
		fta_append(&(map->points), &point, 1);
		if (point.z > map->z_max)
			map->z_max = point.z;
		else if (point.z < map->z_min)
			map->z_min = point.z;
		while (!ft_isspace(*line) && *line != '\0')
			line++;
		while (ft_isspace(*line))
			line++;
		point.x++;
	}
	map->dim.x = point.x + 1;
}

s_fdf_map fdf_parse(const char* filename)
{
	int       fd = open(filename, O_RDONLY);
	char*     line = NULL;
	s_fdf_map map = NEW_FDF_MAP;
	int       line_nb = 0;

	if (fd != -1)
	{
		while (get_next_line(fd, &line) == 1)
		{
			parse_fdf_line(line, &map, line_nb);
			line_nb++;
			free(line);
		}
		map.dim.y = line_nb;
		close(fd);
	}
	return map;
}
