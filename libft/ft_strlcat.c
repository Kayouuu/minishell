/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:39:07 by lbattest          #+#    #+#             */
/*   Updated: 2021/11/05 12:06:49 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = ft_strlen(dest);
	if (dstsize < count || dstsize == 0)
		return (ft_strlen(src) + dstsize);
	while (src[i] && i + count < dstsize - 1)
	{
		dest[i + count] = src[i];
		i++;
	}
	dest[i + count] = '\0';
	return (count + ft_strlen(src));
}
