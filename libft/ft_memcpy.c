/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:48:27 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/07 10:39:39 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copy the content of a memory to another and return it */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			counter;

	d = dest;
	s = (unsigned char *) src;
	counter = 0;
	if (d == ((void *)0) && s == ((void *)0))
		return (0);
	while (counter < size)
	{
		d[counter] = s[counter];
		counter++;
	}
	return (dest);
}
