/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:43:27 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/04 14:11:51 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Fill te memory of a given adress with a specific value */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t size)
{
	size_t			counter;
	unsigned char	*dest;

	counter = 0;
	dest = pointer;
	while (counter < size)
	{
		dest[counter] = value;
		counter++;
	}
	return (pointer);
}
