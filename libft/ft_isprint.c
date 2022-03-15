/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:49:53 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/03 10:37:58 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return 1 if the character is printable, else 0 */

#include "libft.h"

int	ft_isprint(int character)
{
	if (character < 32 || character > 126)
		return (0);
	return (1);
}
