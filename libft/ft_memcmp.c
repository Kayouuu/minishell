/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 09:04:49 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/07 14:08:43 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return the difference between the first two differents values 			  */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = str1;
	s2 = str2;
	if (n != 0)
	{
		if (*s1++ != *s2++)
			return (*--s1 - *--s2);
		while (--n != 0)
		{
			if (*s1++ != *s2++)
				return (*--s1 - *--s2);
		}
	}
	return (0);
}
