/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:50:09 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/03 10:36:38 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert an uppercase character into a lowercase one and return the result, */
/* either converted or not 													  */

#include "libft.h"

int	ft_tolower(int character)
{
	if (character < 65 || character > 90)
		return (character);
	return (character + 32);
}
