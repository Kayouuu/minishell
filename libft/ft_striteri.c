/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:44:23 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/10 08:54:38 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Apply character by character a function passed in parameter using an index */
/* and a character adress													  */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	counter;

	counter = 0;
	if (s == 0 || (*f) == 0)
		return ;
	while (s[counter])
	{
		(*f)(counter, &s[counter]);
		counter++;
	}
}
