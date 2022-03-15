/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:45:23 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/07 12:06:36 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Like ft_memcpy but protected of overflow */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char			*d;
	unsigned char	*s;
	char			*lastd;
	char			*lasts;

	d = dest;
	s = (unsigned char *) src;
	if (dest == ((void *)0) && src == ((void *)0))
		return (0);
	if (dest < src)
		while (size--)
			*d++ = *s++;
	else
	{
		lastd = (char *)dest + (size - 1);
		lasts = (char *)src + (size - 1);
		while (size--)
		{
			*lastd-- = *lasts--;
		}
	}
	return (dest);
}
