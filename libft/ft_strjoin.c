/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:42:03 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/12 13:27:44 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Create by concatenating two strings using malloc and return it             */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		counter;
	int		counter_new_str;
	char	*new_str;

	counter = 0;
	counter_new_str = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (0);
	while (s1[counter])
	{
		new_str[counter_new_str++] = s1[counter];
		counter++;
	}
	counter = 0;
	while (s2[counter])
	{
		new_str[counter_new_str++] = s2[counter];
		counter++;
	}
	new_str[counter_new_str] = '\0';
	return (new_str);
}
