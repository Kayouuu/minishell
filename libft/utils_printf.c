/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:51:09 by lbattest          #+#    #+#             */
/*   Updated: 2022/02/17 10:54:22 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_mod(char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr_mod(char *s)
{
	int	i;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		ft_putchar_mod(s[i]);
		i++;
	}
	return (ft_strlen(s));
}

static void	ft_recursive(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_mod('-');
		n = -n;
	}
	if (n > 9)
		ft_recursive(n / 10);
	ft_putchar_mod(n % 10 + '0');
}

int	ft_putnbr_mod(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		ft_recursive(n);
		return (11);
	}
	ft_recursive(n);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		len++;
		n = n / 10;
	}
	len++;
	return (len);
}
