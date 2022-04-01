/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:25:11 by lbattest          #+#    #+#             */
/*   Updated: 2021/11/10 15:25:43 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ndst;
	unsigned char	*nsrc;

	ndst = dst;
	nsrc = (unsigned char *)src;
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			ndst[len] = nsrc[len];
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
