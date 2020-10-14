#include "fdf.h"

#include <ft_printf.h>
#include <ft_string_legacy.h>
#include <libft.h>
#include <stdlib.h>

#define USAGE_STRING													\
	"Usage: fdf [OPTION]... FILE\n"										\
	"\nOptions:\n"														\
	"\t-w --width   INT  : set the window's width\n"					\
	"\t-h --height  INT  : set the window's height\n"					\
	"\t-t --title   STR  : set the window's title\n"					\
	"\t-o --output  FILE : run in headlessmode, and output to a bmp\n"	\
	"\t-v --version      : display the program's version and exit\n"	\
	"\t--help            : display this usage message and exit"

static void free_charp(char** variable)
{
	free(*variable);
}

int main(int ac, char** av)
{
	const char* program_name = *av;
	t_dimension dim = MAKE_POINT(unsigned, 1280, 720);
	char*       title __attribute__((cleanup (free_charp))) = ft_strdup("Fil de Fer");
	char*       out_file __attribute__((cleanup (free_charp))) = ft_strdup("");

	while (ac-- > 0 && *++av != NULL)
	{
		bool        is_long;
		const char* name  = NULL;
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
			ft_putendl(USAGE_STRING);
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
			ft_putendl_fd(USAGE_STRING, 2);
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
		else if (is_long ? ft_strequ(name, "output") : *name == 'o')
		{
			free(title);
			out_file = ft_strdup(value);
		}
	}
	if (ac == 0)
	{
		ft_putendl_fd("You need to provide a filename.\n" USAGE_STRING, 2);
		return 2;
	}
	if (*out_file != '\0')
		return headless(program_name, *av, dim, out_file);
	else
		return fdf_start(program_name, *av, dim, title);
}
