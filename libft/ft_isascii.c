/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:59:54 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/03 10:38:04 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return 1 if the character is from the ASCII table */

#include "libft.h"

int	ft_isascii(int character)
{
	if (character < 0 || character > 127)
		return (0);
	return (1);
}
