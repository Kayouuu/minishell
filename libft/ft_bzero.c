/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:27:05 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/07 11:42:02 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Clean the memory of a variable by replacing datas with '\0' */

#include "libft.h"

void	ft_bzero(void *pointer, size_t size)
{
	ft_memset((void *)pointer, '\0', (size_t) size);
}
