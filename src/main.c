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
		void*     mlx;
		t_array   windows = fta_new(sizeof(s_window) + sizeof(s_fdf_map));
		s_fdf_map map;

		errno = 0;
		map = fdf_parse(av[1]);
		if (map.points.size == 0)
		{
			perror(av[0]);
			return 1;
		}
		if ((mlx = mlx_init()) == NULL)
		{
			ft_dprintf(2, "%s: MLX initialization failure\n", av[0]);
			return 1;
		}
		fta_reserve(&windows, 1);
		make_window((s_window*)windows.data, mlx, (t_dimension){1280, 720}, "Fil de Fer", FDF_HOOKS);
		*(s_fdf_map*)(windows.data + sizeof(s_window)) = map;
		windows.size += 1;
		mlx_do_key_autorepeaton(mlx);
		mlx_loop(mlx);
		ft_printf("Out of loop\n");
	}
	return 0;
}
