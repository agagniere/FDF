#include "fdf.h"
#include <libft.h>
#include <ft_ctype.h>
#include <get_next_line.h>

#include <stdlib.h>
#include <fcntl.h>

static void parse_fdf_line(const char* line, t_array* points, int line_nb)
{
	s_point3_int point = MAKE_POINT(int, 0, -line_nb, 0);

	while (ft_isspace(*line))
		line++;
	while (*line != '\0')
	{
		point.z = ft_atoi(line);
		fta_append(points, &point, 1);
		while (!ft_isspace(*line) && *line != '\0')
			line++;
		while (ft_isspace(*line))
			line++;
		point.x++;
	}
}

t_array parse_fdf(const char* filename)
{
	int     fd = open(filename, O_RDONLY);
	char*   line = NULL;
	t_array points = NEW_ARRAY(s_point3_int);
	int     line_nb = 0;

	if (fd != -1)
	{
		while (get_next_line(fd, &line) == 1)
		{
			parse_fdf_line(line, &points, line_nb);
			line_nb++;
			free(line);
		}
		close(fd);
	}
	return points;
}
