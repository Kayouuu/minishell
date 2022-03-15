/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:41:40 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/03 10:36:29 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert a lowercase character into an uppercase one and return the result, */
/* either converted or not 													  */

#include "libft.h"

int	ft_toupper(int character)
{
	if (character < 97 || character > 122)
		return (character);
	return (character - 32);
}
