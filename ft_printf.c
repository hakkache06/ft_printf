

#include "ft_printf.h"

int					ft_printf(const char *fr, ...)
{
	va_list			ap;
	size_t			len;

	va_start(ap, fr);
	len = ft_reception_struct(fr, ap);
	va_end(ap);
	return (len);
}
