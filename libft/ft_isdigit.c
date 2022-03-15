/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:49:29 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/04 13:15:11 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return 1 if the character is a digital number, else 0 */

#include "libft.h"

int	ft_isdigit(int character)
{
	if (character < 48 || character > 57)
		return (0);
	return (1);
}
