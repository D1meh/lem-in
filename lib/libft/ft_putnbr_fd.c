#include "../../includes/lib.h"

void	ft_putnbr_fd(int fd, int n)
{
	long int	nb;
	char		c;

	nb = n;
	if (n < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(fd, nb / 10);
		c = (nb % 10) + '0';
		write(fd, &c, 1);
	}
	else
	{
		c = nb + '0';
		write(fd, &c, 1);
	}
}