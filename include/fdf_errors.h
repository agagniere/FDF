#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <ft_printf.h>

typedef struct fdf_error t_fdf_error;

struct fdf_error
{
	const char* description;
	const char* function;
	const char* file;
	int         line;
	bool        to_be_freed;
};

#define FDF_NO_ERROR                  FDF_ERROR_STATIC(NULL)
#define FDF_ERROR_MALLOC_FAILED       FDF_ERROR_STATIC("Failed to allocate memory.")
#define FDF_ERROR_STATIC(DESCRIPTION) _FDF_ERROR(DESCRIPTION, false)
#define FDF_ERROR(DESCRIPTION)        _FDF_ERROR(DESCRIPTION, true)
#define FDF_IS_ERROR(ERROR)           (ERROR.description != NULL)

#define RETURN_FDF_ERROR(DESC, ...)                    \
	do                                                 \
	{                                                  \
		char* error_desc;                              \
		ft_asprintf(&error_desc, DESC, ##__VA_ARGS__); \
		return FDF_ERROR(error_desc);                  \
	} while (0)

/* Print error if needed, else return 0 */
int fdf_return(const char* program_name, t_fdf_error error);

/*
** private:
*/

#define _FDF_ERROR(DESCRIPTION, ALLOCATED)                \
    (struct fdf_error)                                    \
    {                                                     \
        .description = DESCRIPTION,                       \
        .function = __FUNCTION__,                         \
        .file = __FILE__,                                 \
        .line = __LINE__,                                 \
        .to_be_freed = ALLOCATED,                         \
    }
