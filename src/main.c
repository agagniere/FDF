#include "fdf.h"

#include <libft.h>
#include <ft_printf.h>
#include <ft_string_legacy.h>
#include <mlx.h>

#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/*
** A major non-POSIX OS, Android,
** still defines M_PI and others.
*/

static void init_fdf(s_fdf_env* env)
{
	env->offset.x = env->win.dim.x / 2;
	env->offset.y = env->win.dim.y / 2;
	env->zoom = env->win.dim.x / env->map.dim.x / 2;
	env->rotation.z = M_PI_4;
	env->rotation.x = M_PI_4;
	fdf_repaint(env);
}

static int fdf_start(const char* program_name, const char* filename,
					 t_dimension dim, const char* title)
{
	void*     mlx;
	t_array   windows = NEW_ARRAY(s_fdf_env);
	s_fdf_env fdf = NEW_FDF_ENV;

	errno = 0;
	fdf.map = fdf_parse(filename);
	if (fdf.map.points.size == 0)
	{
		perror(program_name);
		return 3;
	}
	if ((mlx = mlx_init()) == NULL
		|| !make_window(&fdf.win, mlx, dim, title, FDF_HOOKS)
		|| fta_append(&windows, &fdf, 1) != 0)
	{
		ft_dprintf(2, "%s: MLX initialization failure\n", program_name);
		return 4;
	}
	init_fdf(&fdf);
	mlx_do_key_autorepeaton(mlx);
	mlx_loop(mlx);
	ft_putendl("===== Out of loop =====");
	return 0;
}

static void free_charp(char** variable)
{
	free(*variable);
}

int main(int ac, char** av)
{
	const char* program_name = *av;
	t_dimension dim = MAKE_POINT(unsigned, 1280, 720);
	char*       title __attribute__((cleanup (free_charp))) = ft_strdup("Fil de Fer");

	while (ac-- > 0 && *++av != NULL)
	{
		bool        is_long;
		const char* name = NULL;
		char*       value = NULL;

		if (**av != '-' || ((is_long = (*++*av == '-')) && !*++*av && av++ && ac--))
			break;
		name = *av;
		if (!is_long)
		{
			if (!*++*av)
			{
				ac--;
				av++;
			}
			value = *av;
		}
		else if ((value = ft_strchr(*av, '=')))
			*value++ = '\0';
		else
		{
			ac--;
			value = *++av;
		}

		if (is_long && ft_strequ(name, "help"))
		{
			ft_putendl("Usage: fdf [OPTION]... FILE");
			ft_putendl("\nOptions:");
			ft_putendl("\t-w --width    : set the window's width");
			ft_putendl("\t-h --height   : set the window's height");
			ft_putendl("\t-t --title    : set the window's title");
			ft_putendl("\t-v --version  : display the program's version and exit");
			ft_putendl("\t--help        : display this usage message and exit");
			return 0;
		}
		if (is_long ? ft_strequ(name, "version") : *name == 'v')
		{
			ft_putendl("Fil de Fer version 1.0");
			return 0;
		}
		if (value == NULL)
		{
			ft_dprintf(2, "%s: Option \"%.*s\" requires an argument.\n", program_name, (is_long ? 30 : 1), name);
			ft_dprintf(2, "Try '%s --help' for more information.\n", program_name);
			return 1;
		}

		if (is_long ? ft_strequ(name, "width") : *name == 'w')
			dim.x = ft_atoi(value);
		else if (is_long ? ft_strequ(name, "height") : *name == 'h')
			dim.y = ft_atoi(value);
		else if (is_long ? ft_strequ(name, "title") : *name == 't')
		{
			free(title);
			title = ft_strdup(value);
		}
	}
	if (ac == 0)
	{
		ft_dprintf(2, "Usage: fdf [OPTION]... FILE\n\n");
		ft_dprintf(2, "You need to rovide a filename.\n");
		ft_dprintf(2, "Try '%s --help' for more information.\n");
		return 2;
	}
	return fdf_start(program_name, *av, dim, title);
}
