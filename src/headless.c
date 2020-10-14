#include "bmp.h"
#include "ft_printf.h"

int headless()
{
	ft_dprintf(2, "%s()", __FUNCTION__);
	return 0;
}
