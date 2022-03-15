/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:33:56 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/09 15:20:20 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Concatenate two strings, dest after src and return the size */
/* of the new string 										   */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	n;
	size_t	len;
	size_t	dest_size;
	size_t	src_size;

	n = 0;
	len = 0;
	dest_size = ft_strlen(dest);
	src_size = ft_strlen((const char *)src);
	if (size < dest_size || size == 0)
		return (src_size + size);
	len = dest_size;
	while (src[n] != '\0' && len < size - 1)
	{
		dest[len] = src[n];
		n++;
		len++;
	}
	dest[len] = '\0';
	return (dest_size + src_size);
}
