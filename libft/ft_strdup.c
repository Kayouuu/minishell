/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:38:50 by lbattest          #+#    #+#             */
/*   Updated: 2021/11/07 14:35:22 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char	*s1)
{
	int		i;
	char	*array_ptr;

	array_ptr = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!array_ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		array_ptr[i] = s1[i];
		i++;
	}
	array_ptr[i] = '\0';
	return (array_ptr);
}
