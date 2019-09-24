#include "fdf.h"
#include <ft_printf.h>
#include <mlx.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char** av)
{
	if (ac > 1)
	{
		s_env env;
		errno = 0;
		env.points = parse_fdf(av[1]);
		if (env.points.size == 0)
		{
			perror(av[0]);
			return 1;
		}
		if ((env.mlx = mlx_init()) == NULL)
		{
			ft_dprintf(2, "%s: MLX initialization failure\n", av[0]);
			return 1;
		}
		env.windows = NEW_ARRAY(s_window);
		add_window(&env, MAKE_POINT(t_dimension, 1280, 720), "Fil de Fer");
		mlx_loop(env.mlx);
	}
	return 0;
}
