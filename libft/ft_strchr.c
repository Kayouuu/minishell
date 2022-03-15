/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:22:07 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/11 10:04:59 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return the pointer of the first occurence of */
/* the character c in the string str 			*/

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if ((unsigned char)str[n] == (unsigned char)c
			&& (unsigned char)c != '\0')
			return ((char *) &str[n]);
		n++;
	}
	if (c == '\0')
		return ((char *) &str[n]);
	return (0);
}
