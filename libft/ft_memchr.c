/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:16 by lbattest          #+#    #+#             */
/*   Updated: 2021/11/15 15:43:34 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*a;

	i = 0;
	a = (char *)s;
	while (n > i)
	{
		if (a[i] == (char)c)
			return ((void *)&s[i]);
		i++;
	}
	return (0);
}
