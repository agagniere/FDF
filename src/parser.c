#include "fdf.h"

#include <ft_ctype.h>
#include <ft_printf.h>
#include <get_next_line.h>
#include <libft.h>

#include <fcntl.h>

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int parse_fdf_line(const char* line, t_fdf_map* map)
{
	t_point3_int point = MAKE_POINT(int, 0, map->dim.y, 0);

	while (ft_isspace(*line))
		line++;
	while (*line != '\0')
	{
		point.z = ft_atoi(line);
		if ((fta_append(&(map->points), &point, 1)) != 0)
			return -2;
		if (point.z > map->z_max)
			map->z_max = point.z;
		else if (point.z < map->z_min)
			map->z_min = point.z;
		if (*line == '-' || *line == '+')
			line++;
		while (ft_isdigit(*line))
			line++;
		if (*line == ',') // TODO : parse hex color, store it with the point and use it
			while (ft_isalnum(*++line));
		if (!ft_isspace(*line) && *line != '\0')
			return -1;
		while (ft_isspace(*line))
			line++;
		point.x++;
	}
	return point.x;
}

void close_fd(int* fd)
{
	if (*fd > 0)
		close(*fd);
}

t_fdf_error fdf_parse(const char* filename, t_fdf_map* out_map)
{
	int __attribute__((cleanup(close_fd))) fd = 0;
	char* line = NULL;
	int   line_size, line_nb = 0;

	errno = 0;
	if ((filename[0] != '-' || filename[1] != '\0') && (fd = open(filename, O_RDONLY)) == -1)
		RETURN_FDF_ERROR("Unable to open input file \"%s\" : %s", filename, strerror(errno));
	out_map->dim = MAKE_POINT(unsigned, 0, 0);
	while (get_next_line(fd, &line) == 1)
	{
		++line_nb;
		line_size = parse_fdf_line(line, out_map);
		free(line);
		if (line_size == -1)
			RETURN_FDF_ERROR("File \"%s\" is invalid : wrong format (line %u) Expected line format : \"(\\s*[+-]?\\d+(,0[xX][0-9a-fA-F]+)?)*\\s*\" e.g. \"0 1 2,0xf0f0f0 1 0\"", (fd ? filename : "<stdin>"), line_nb);
		else if (line_size == -2)
			return FDF_ERROR_MALLOC_FAILED;
		else if (line_size == 0)
			continue;
		else if (out_map->dim.y > 1 && (unsigned)line_size != out_map->dim.x)
			RETURN_FDF_ERROR("Object described in file \"%s\" is invalid : all lines are not the same length. (line %u)", (fd ? filename : "<stdin>"), line_nb);
		out_map->dim.y++;
		out_map->dim.x = line_size;
	}
	if (out_map->dim.x * out_map->dim.y < 2)
		RETURN_FDF_ERROR("Object described in file \"%s\" is invalid : (%i, %i) is not a valid dimension, it should have at least 2 points", (fd ? filename : "<stdin>"), out_map->dim.x, out_map->dim.y);
	return FDF_NO_ERROR;
}
