/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:39:26 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/07 10:59:52 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
/*	Cut from i to j and free str	*/

char	*ft_strcut(char *str, int i, int j)
{
	char	*new_str;
	int		n;
	int		k;

	n = -1;
	k = 0;
	if (j < i)
		return (str);
	new_str = malloc(sizeof(char) * (ft_strlen(str) - (j - i) + 1));
	if (!new_str)
	{
		ft_putendl_fd("Malloc error", 2);
		exit(0);
	}
	while (str[++n])
		if (n < i || n > j)
			new_str[k++] = str[n];
	new_str[k] = '\0';
	free(str);
	return (new_str);
}
