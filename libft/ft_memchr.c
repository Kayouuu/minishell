/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 08:32:40 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/04 14:09:00 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return the pointer of the first occurence of searchedChar in memoryBlock.  */
/* If not found, return 0       											  */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t	counter;

	counter = 0;
	while (counter < size)
	{
		if (*(char *)memoryBlock == (char) searchedChar)
			return ((void *)memoryBlock);
		memoryBlock++;
		counter++;
	}
	return (0);
}
