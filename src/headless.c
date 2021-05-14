#include "fdf.h"
#include "bmp.h"

#include <ft_printf.h>

#include <stdlib.h>

int headless(const char* program_name, const char* input_file_name, t_dimension dim, const char* output_file_name, int benchmark_iterations)
{
	t_fdf_env fdf = NEW_FDF_ENV;

	ft_dprintf(2, "%s(%s, %s, %s)\n", __FUNCTION__, program_name, input_file_name, output_file_name);
	fdf.win.dim = dim;
	fdf.map = fdf_parse(input_file_name);
	fdf_init(&fdf);
	fdf.win.pixels = malloc(sizeof(int) * dim.x * dim.y);
	while (benchmark_iterations --> 0)
		fdf_repaint(&fdf);
	generateBitmapImage(fdf.win.pixels, dim.y, dim.x, output_file_name);
	free(fdf.win.pixels);
	return 0;
}
