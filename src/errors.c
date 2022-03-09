#include "fdf.h"

#include <ft_printf.h>

#include <errno.h>
#include <stdlib.h>

int fdf_return(const char* program_name, t_fdf_error error)
{
	if (error.description == NULL)
		return EXIT_SUCCESS;
	ft_dprintf(2, "[FATAL ERROR] (%s %s@%s:%i) : %s.\n", program_name, error.function, error.file, error.line, error.description);
	if (error.to_be_freed)
		free((char*)error.description);
	return EXIT_FAILURE;
}
