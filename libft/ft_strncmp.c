/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:46:14 by psaulnie          #+#    #+#             */
/*   Updated: 2021/12/24 10:53:24 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return the difference between the first two differents characters */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	n;

	n = 0;
	while (n < length && (first[n] || second[n]))
	{
		if (first[n] != second[n])
			return ((unsigned char)first[n] - second[n]);
		n++;
	}
	return (0);
}
