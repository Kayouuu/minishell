/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:39:23 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/03 10:38:07 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return 1 if the character is an alphabetical letter, else 0 */

#include "libft.h"

int	ft_isalpha(int character)
{
	if (character < 65 || character > 122)
		return (0);
	if (character > 90 && character < 97)
		return (0);
	return (1);
}
