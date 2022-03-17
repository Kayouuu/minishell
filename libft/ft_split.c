/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:52:10 by lbattest          #+#    #+#             */
/*   Updated: 2021/12/17 11:39:13 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char sep)
{
	int		i;
	int		j;
	int		word;

	i = 0;
	word = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] == sep && s[i])
			i++;
		while (s[i] != sep && s[i])
		{
			if (j == 0)
				word++;
			i++;
			j++;
		}
	}
	return (word);
}

static char	*ft_strdupmod(char const *s, char c, int start)
{
	char	*str;
	int		i;

	i = 0;
	while (s[start + i] != c && s[start + i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	i = 0;
	while (s[start + i] != c && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	*free_all(char **str, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(str[i++]);
	free(str);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	int		i;
	int		j;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	splitted = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!splitted)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			break ;
		splitted[j++] = ft_strdupmod(s, c, i);
		if (!splitted[j - 1])
			return (free_all(splitted, i));
		while (s[i] != c && s[i])
			i++;
	}
	splitted[word_count(s, c)] = 0;
	return (splitted);
}
