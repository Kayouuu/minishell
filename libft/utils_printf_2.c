/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printf_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:51:29 by lbattest          #+#    #+#             */
/*   Updated: 2022/02/17 10:55:48 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	to_hexa(uint32_t nbr, char *base)
{
	int			i;
	uint32_t	n;
	char		str[9];

	n = nbr;
	i = 0;
	if (!n)
		i = 1;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = base[nbr % 16];
		nbr = nbr / 16;
		i--;
	}
	return (ft_putstr_mod(str));
}

int	adress(uint64_t nbr)
{
	int			i;
	uint64_t	n;
	char		str[20];
	char		*hexa;

	hexa = "0123456789abcdef";
	n = nbr;
	i = 0;
	if (!n)
		i = 1;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = hexa[nbr % 16];
		nbr = nbr / 16;
		i--;
	}
	return (ft_putstr_mod(str));
}

static void	ft_unsigned_recursive(unsigned int n)
{
	if (n > 9)
		ft_unsigned_recursive(n / 10);
	ft_putchar_mod(n % 10 + '0');
}

int	ft_uns_putnbr_mod(unsigned int n)
{
	int	len;

	len = 0;
	ft_unsigned_recursive(n);
	while (n > 9)
	{
		len++;
		n = n / 10;
	}
	len++;
	return (len);
}
