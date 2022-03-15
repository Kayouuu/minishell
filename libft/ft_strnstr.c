/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:28:17 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/07 15:33:25 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Find the first occurence of a substring in a string and return his pointer */

#include "libft.h"

char	*ft_strnstr(const char *str, char const *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == needle[j] && (i + j) < n)
		{
			if (needle[j] == '\0' && str[i + j] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (0);
}
