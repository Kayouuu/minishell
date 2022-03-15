/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 08:41:31 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/11 11:03:44 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert an integer into a string and return it 							  */

#include "libft.h"

static int	ft_nbr_size(int n)
{
	int	size;
	int	nbr;

	size = 0;
	nbr = n;
	if (nbr == -2147483647 - 1)
		return (11);
	if (nbr < 0)
	{
		nbr *= -1;
		size++;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		size++;
	}
	size++;
	return (size);
}

static void	reverse(char *str, int size)
{
	int		counter;
	char	tmp;

	counter = 0;
	tmp = 0;
	while (counter <= size / 2)
	{
		tmp = str[size - counter];
		str[size - counter] = str[counter];
		str[counter] = tmp;
		counter++;
	}
}

static void	convert(char *str, int n)
{
	int	num;
	int	counter;

	counter = 0;
	num = 0;
	while (n)
	{
		num = n % 10;
		if (num > 9)
			str[counter++] = 65 + (num - 10);
		else
			str[counter++] = 48 + num;
		n /= 10;
	}
}

static char	*particular_cases(int n, char *str)
{
	if (n == -2147483647 - 1)
	{
		ft_memcpy(str, "-2147483648\0", 12);
		return (str);
	}
	else if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	int		is_negative;
	int		nbr;
	char	*str;

	is_negative = 0;
	nbr = ft_nbr_size(n);
	str = malloc(sizeof(char) * (nbr + 1));
	if (!str)
		return (0);
	if (n == 0 || n == -2147483647 - 1)
		return (particular_cases(n, str));
	if (n < 0)
	{
		is_negative = 1;
		n *= -1;
	}
	convert(str, n);
	if (is_negative)
		str[nbr - 1] = '-';
	str[nbr] = '\0';
	reverse(str, nbr - 1);
	return (str);
}
