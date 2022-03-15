/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:25:21 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/11 10:18:17 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocate and clean a memory block with the value 0 and return his pointer */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	int		*allocated_memory;

	allocated_memory = malloc(elementSize * elementCount);
	if (!allocated_memory)
		return (0);
	ft_bzero(allocated_memory, elementCount * elementSize);
	return (allocated_memory);
}
