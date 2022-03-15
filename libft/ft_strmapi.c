/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:40:39 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/10 08:53:16 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Apply character by character a function passed in parameter using an index */
/* and a character adress, then apply it on a string 						  */
/* that the function return  												  */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	counter;
	char			*new_str;

	if (s == 0 || (*f) == 0)
		return (0);
	counter = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_str)
		return (0);
	while (s[counter])
	{
		new_str[counter] = (*f)(counter, s[counter]);
		counter++;
	}
	new_str[counter] = '\0';
	return (new_str);
}
