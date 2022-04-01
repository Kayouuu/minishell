/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stridup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:36:02 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/18 12:38:30 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Stridup function : duplicate an str from start index to end index
*/

char	*ft_stridup(char *str, int start, int end)
{
	char	*returned_str;
	int		i;

	i = 0;
	if (start == end)
		end++;
	returned_str = malloc(sizeof(char) * (end - start + 1));
	if (!returned_str)
		return (NULL);
	while (str[start] && start < end)
	{
		returned_str[i] = str[start];
		i++;
		start++;
	}
	returned_str[i] = '\0';
	return (returned_str);
}
