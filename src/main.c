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

#define _RETURN_FDF_ERROR_(MSG, ...)                            \
	do                                                          \
	{                                                           \
		char* error_desc;                                       \
		USAGE(2, program_name);                                 \
		ft_asprintf(&error_desc, MSG, ##__VA_ARGS__);           \
		return fdf_return(program_name, FDF_ERROR(error_desc)); \
	} while (0)

static void free_charp(char** variable)
{
	free(*variable);
}

int main(int ac, char** av)
{
	const char*  program_name = *av;
	t_point2_int dim          = MAKE_POINT(int, 1280, 720);
	char*    title __attribute__((cleanup(free_charp))) = ft_strdup("Fil de Fer");
	char* out_file __attribute__((cleanup(free_charp))) = ft_strdup("");
	int   benchmark_iterations                          = 1;

	while (ac-- > 0 && *++av != NULL)
	{
		bool        is_long = false;
		const char* name    = NULL;
		char*       value   = NULL;

		// code that requires inline comments -> bad code
		if (**av != '-' || (*av)[1] == '\0') // single dash or not starting with dash -> not an option
			break;
		++*av; // we can now exclude the leading dash
		if (**av == '-')
		{
			++*av;
			if (**av == '\0') // lone double-dash -> end of options
			{
				av++;
				ac--;
				break;
			}
			is_long = true; // starting with double-dash -> long option
		}
		name = *av;
		if (!is_long)
		{
			if (!*++*av)
			{ // -k value
				ac--;
				av++;
			} // else -kvalue
			value = *av;
		}
		else if ((value = ft_strchr(*av, '=')))
			*value++ = '\0'; // --key=value
		else
		{ // --key value
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
			_RETURN_FDF_ERROR_("Option \"%.*s\" requires an argument", (is_long ? 30 : 1), name);
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
		else
			_RETURN_FDF_ERROR_("Unknown option \"%.*s\"", (is_long ? 30 : 1), name);
	}

	if (ac == 0)
		_RETURN_FDF_ERROR_("Please provide an input file");
	else if (dim.x < 1 || dim.y < 1)
		_RETURN_FDF_ERROR_("Image dimension must be positive, it cannot be (%i, %i)", dim.x, dim.y);
	else if (benchmark_iterations < 1)
		_RETURN_FDF_ERROR_("The number of iterations for benchmark must be positive, it cannot be %i", benchmark_iterations);
	else if (benchmark_iterations > 1 && *out_file == '\0')
		_RETURN_FDF_ERROR_("The \"benchmark\" option has no effect when not in headless mode. It is to be used in conjunction with the \"output\" option");

	if (*out_file != '\0')
		return fdf_return(program_name, headless(*av, MAKE_POINT(unsigned, dim.x, dim.y), out_file, benchmark_iterations));
	else
		return fdf_return(program_name, fdf_start(*av, MAKE_POINT(unsigned, dim.x, dim.y), title));
}
