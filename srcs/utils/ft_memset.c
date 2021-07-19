#include "utils.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ch;

	ch = (unsigned char *)b;
	while (len > 0)
		ch[--len] = c;
	return (b);
}
