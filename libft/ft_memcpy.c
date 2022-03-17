/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:05:48 by lbattest          #+#    #+#             */
/*   Updated: 2021/11/08 10:27:49 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ndest;
	unsigned char	*nsrc;
	unsigned int	i;

	ndest = dest;
	nsrc = (unsigned char *)src;
	i = 0;
	if (dest == 0 && src == 0)
		return (dest);
	while (n > i)
	{
		ndest[i] = nsrc[i];
		i++;
	}
	return (dest);
}
