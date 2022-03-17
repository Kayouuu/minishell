/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:52:32 by lbattest          #+#    #+#             */
/*   Updated: 2021/11/15 16:07:03 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_sep(char c, char const *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	int		j;
	char	*str;
	int		len;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (is_sep(s1[i], set) == 1)
		i++;
	while (is_sep(s1[j], set) == 1 && j != 0)
		j--;
	len = j - i;
	str = ft_substr(s1, i, len + 1);
	if (!str)
		return (0);
	return (str);
}
