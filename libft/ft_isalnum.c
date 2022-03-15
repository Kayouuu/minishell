/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:06:11 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/03 10:38:10 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return 1 if the character is a letter or a number, else 0 */

#include "libft.h"

int	ft_isalnum(int character)
{
	if (character < 48 || character > 122)
		return (0);
	if (character > 57 && character < 65)
		return (0);
	if (character > 90 && character < 97)
		return (0);
	return (1);
}
