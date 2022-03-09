#include "bmp.h"
#include "fdf.h"

#include <ft_printf.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

t_fdf_error
headless(const char* input_file_name, t_dimension dim, const char* output_file_name, int benchmark_iterations)
{
	t_fdf_env   fdf   = NEW_FDF_ENV;
	t_fdf_error error = fdf_parse(input_file_name, &fdf.map);

	if (FDF_IS_ERROR(error))
		return error;
	fdf.win.dim = dim;
	fdf_init(&fdf);
	if ((fdf.win.pixels = malloc(sizeof(int) * dim.x * dim.y)) == NULL)
		return FDF_ERROR_MALLOC_FAILED;
	while (benchmark_iterations --> 0)
		fdf_repaint(&fdf);
	errno = 0;
	if (!generateBitmapImage(fdf.win.pixels, dim.y, dim.x, output_file_name))
		RETURN_FDF_ERROR("Issue encountered with the output file \"%s\" : %s", output_file_name, strerror(errno));
	free(fdf.win.pixels);
	return FDF_NO_ERROR;
}
