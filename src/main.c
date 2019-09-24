#include "fdf.h"
#include <ft_printf.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


char* point_to_string(s_point3_int* point)
{
	char *str;
	ft_asprintf(&str, "(%i, %i, %i)", point->x, point->y, point->z);
	return str;
}

int main(int ac, char** av)
{
	if (ac > 1)
	{
		s_env env;
		errno = 0;
		env.points = parse_fdf(av[1]);
		if (env.points.size == 0)
			perror(av[0]);
		{
			char* str = fta_string(&(env.points), (char*(*)(void*))point_to_string);
			ft_printf("%s\n", str);
			free(str);
		}
	}
	return 0;
}
