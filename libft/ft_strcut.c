/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:39:26 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/04 16:52:56 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Cut from i to j and free str	*/

char	*ft_strcut(char *str, int i, int j)
{
	char	*new_str;
	int		n;
	int		k;

	n = 0;
	k = 0;
	if (j < i)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) - (j - i) + 1));
	while (str[n])
	{
		if (n < i || n > j)
		{
			new_str[k] = str[n];
			k++;
		}
		n++;
	}
	new_str[n] = '\0';
	free(str);
	return (new_str);
}
