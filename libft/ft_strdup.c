/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:35:34 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/07 11:49:24 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Duplicate a string using malloc and return it */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		counter;
	int		length;

	length = ft_strlen(src);
	dest = malloc(sizeof(char) * length + 1);
	counter = 0;
	if (!dest)
		return (0);
	while (counter < length)
	{
		dest[counter] = src[counter];
		counter++;
	}
	dest[counter] = '\0';
	return (dest);
}
