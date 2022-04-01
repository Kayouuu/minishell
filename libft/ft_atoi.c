/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:18:16 by lbattest          #+#    #+#             */
/*   Updated: 2022/02/24 14:55:17 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_whitespace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

long int	ft_atoi(const char *str)
{
	size_t			i;
	int				s;
	long int		num;

	num = 0;
	i = 0;
	s = 1;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + s * (str[i] - '0');
		i++;
	}
	return (num);
}
