/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:14:23 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/12 13:27:02 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Create a new string with an old one by trimming a part */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	counter;

	counter = 0;
	if (s == 0)
		return (0);
	if (start >= ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (0);
		ft_memcpy(str, "\0", 1);
		return (str);
	}
	if (len > ft_strlen(s))
		str = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (counter < len && s[start])
		str[counter++] = s[start++];
	str[counter] = '\0';
	return (str);
}
