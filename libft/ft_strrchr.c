/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:33:17 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/11 10:06:17 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return the pointer of the last occurence of */
/* the character c in the string str 		   */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		n;
	char	*pointer_address;
	int		occurence;

	n = 0;
	occurence = 0;
	pointer_address = 0;
	while (str[n])
	{
		if ((unsigned char)str[n] == (unsigned char)c
			&& (unsigned char)c != '\0')
		{
			pointer_address = (char *) &str[n];
			occurence = 1;
		}
		n++;
	}
	if (c == '\0')
		return ((char *) &str[n]);
	if (occurence)
		return (pointer_address);
	return (0);
}
