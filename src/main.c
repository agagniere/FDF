#include "fdf.h"

#include <ft_printf.h>
#include <ft_string_legacy.h>
#include <libft.h>
#include <stdlib.h>

#define OPTIONS_STRING \
	"Options:\n" \
	"Global:\n" \
	"  -w, --width=INT      set the window's width\n" \
	"  -h, --height=INT     set the window's height\n" \
	"Graphical mode:\n" \
	"  -t, --title=STR      set the window's title\n" \
	"Headless:\n" \
	"  -o, --output=FILE    run in headlessmode, and output to a bmp\n" \
	"  -b, --benchmark=INT  in headless mode, render the frame INT times\n" \
	"Misc:\n"\
	"  -v, --version        display the program's version and exit\n" \
	"      --help           display this usage message and exit"

#define USAGE(FD, NAME)	ft_dprintf(FD, "Usage: %s [OPTION]... FILE\n\n%s\n", NAME, OPTIONS_STRING)


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
	int         benchmark_iterations = 1;

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
			USAGE(1, program_name);
			return 0;
		}
		if (is_long ? ft_strequ(name, "version") : *name == 'v')
		{
			ft_putendl("FilDeFer 1.0");
			return 0;
		}
		if (value == NULL)
		{
			ft_dprintf(2, "%s: Option \"%.*s\" requires an argument.\n", program_name, (is_long ? 30 : 1), name);
			USAGE(2, program_name);
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
			free(out_file);
			out_file = ft_strdup(value);
		}
		else if (is_long ? ft_strequ(name, "benchmark") : *name == 'b')
			benchmark_iterations = ft_atoi(value);
	}
	if (ac == 0)
	{
		ft_putendl_fd("You need to provide a filename.\n", 2);
		USAGE(2, program_name);
		return 2;
	}
	if (*out_file != '\0')
		return headless(program_name, *av, dim, out_file, benchmark_iterations);
	else
		return fdf_start(program_name, *av, dim, title);
}
