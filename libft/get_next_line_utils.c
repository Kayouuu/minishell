/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:00:31 by psaulnie          #+#    #+#             */
/*   Updated: 2021/12/21 14:36:12 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

char	*gnl_strndup(const char *src, char c)
{
	char	*dest;
	int		counter;
	int		len;

	counter = 0;
	len = ft_strlen(src);
	while (src[counter] != c)
		counter++;
	if (counter < len && c != '\0')
		len = counter + 1;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	counter = 0;
	while (counter < len)
	{
		dest[counter] = src[counter];
		counter++;
	}
	dest[counter] = '\0';
	return (dest);
}

char	*gnl_strchr(const char *str)
{
	int	n;

	n = 0;
	if (!str)
		return (0);
	while (str[n])
	{
		if (str[n] == '\n')
			return ((char *) &str[n]);
		n++;
	}
	return (0);
}

char	*gnl_strjoin(char *s1, char const *s2)
{
	int		counter;
	int		counter_new_str;
	char	*new_str;

	counter = 0;
	counter_new_str = 0;
	if (s1 == 0)
		new_str = malloc(sizeof(char) * (ft_strlen(s2) + 1));
	else
		new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (0);
	while (s1 != 0 && s1[counter])
	{
		new_str[counter_new_str] = s1[counter];
		counter_new_str++;
		counter++;
	}
	counter = 0;
	while (s2[counter])
		new_str[counter_new_str++] = s2[counter++];
	new_str[counter_new_str] = 0;
	free(s1);
	return (new_str);
}
