/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:46:07 by lbattest          #+#    #+#             */
/*   Updated: 2021/11/16 13:38:32 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(long nu)
{
	int	i;

	i = 0;
	if (nu < 0 || nu == 0)
	{
		nu = -nu;
		i++;
	}
	while (nu / 10 > 0)
	{
		nu = nu / 10;
		i++;
	}
	if (nu > 0 && nu < 10)
		i++;
	return (i);
}

static char	*ft_following(int length, long nu, char *str)
{
	while (length >= 0)
	{
		if (length == 0 && nu <= 0)
			str[length] = '-';
		else
			str[length] = nu % 10 + '0';
		nu = nu / 10;
		length--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	nu;
	int		length;
	char	*str;

	nu = n;
	length = ft_length(nu);
	str = ft_calloc(length + 1, sizeof(char));
	if (str == 0)
		return (0);
	str[length] = '\0';
	if (nu == 0)
	{
		str[0] = '0';
		return (str);
	}
	length--;
	if (nu < 0)
		nu = -nu;
	return (ft_following(length, nu, str));
}
