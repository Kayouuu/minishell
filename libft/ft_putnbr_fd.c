/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:31:36 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/14 09:35:56 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Write the integer n in the file fd										  */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nb;

	nb = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	c = nb % 10 + '0';
	write(fd, &c, 1);
}
