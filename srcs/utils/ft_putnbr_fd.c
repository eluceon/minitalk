#include "utils.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	unsigned int	nb;

	nb = (unsigned int)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	c = nb % 10 + '0';
	write(fd, &c, 1);
}
