/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:11:07 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/10 09:20:17 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert ASCII string to an integer, return 0 if it's not a digital number */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		n;
	long	nb;
	int		negative;

	n = 0;
	nb = 0;
	negative = 1;
	while (str[n] == ' ' || str[n] == '\t' || str[n] == '\n' || str[n] == '\v'
		|| str[n] == '\f' || str[n] == '\r')
		n++;
	if (str[n] == '-')
		negative = -1;
	if (str[n] == '+' || str[n] == '-')
		n++;
	while (str[n] && ft_isdigit(str[n]))
	{
		if ((nb * 10 + (str[n] - '0')) / 10 != nb && negative == -1)
			return (0);
		else if ((nb * 10 + (str[n] - '0')) / 10 != nb)
			return (-1);
		nb *= 10;
		nb += str[n++] - 48;
	}
	return ((int)nb * negative);
}
