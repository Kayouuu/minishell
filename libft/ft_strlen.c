/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:03:25 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/04 14:29:32 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Calculate the length of a string */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}
