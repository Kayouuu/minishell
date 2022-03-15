/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:54:45 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/10 08:52:38 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Remove characters from the start and the end of the string and			  */
/* return a new one 											     		  */

#include "libft.h"

static char	*str_dup(const char *src, int counter_src, int end)
{
	char	*dest;
	int		length;
	int		counter_dest;

	counter_dest = 0;
	length = end - counter_src;
	if (length < 0)
		length = 0;
	dest = malloc(sizeof(char) * (length + 1));
	if (!dest)
		return (0);
	while (counter_dest < length)
	{
		dest[counter_dest] = src[counter_src];
		counter_dest++;
		counter_src++;
	}
	dest[counter_dest] = '\0';
	return (dest);
}

static int	first_trim(char const *s1, char const *set)
{
	int		counter_str;
	int		counter_set;
	int		is_from_set;

	counter_str = 0;
	counter_set = 0;
	is_from_set = 0;
	while (s1[counter_str])
	{
		while (set[counter_set])
		{
			if (set[counter_set] == s1[counter_str])
				is_from_set = 1;
			counter_set++;
		}
		if (!is_from_set)
			break ;
		is_from_set = 0;
		counter_set = 0;
		counter_str++;
	}
	return (counter_str);
}

static int	second_trim(char const *s1, char const *set)
{
	int		counter_set;
	int		is_from_set;
	int		length;

	counter_set = 0;
	length = ft_strlen(s1);
	is_from_set = 1;
	while (is_from_set)
	{
		is_from_set = 0;
		counter_set = 0;
		while (set[counter_set] && length >= 1)
		{
			if (set[counter_set] == s1[length - 1])
				is_from_set = 1;
			counter_set++;
		}
		length--;
	}
	return (length);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		counter_str;
	int		length;
	char	*new_str;

	if (s1 == 0 || set == 0)
		return (0);
	counter_str = first_trim(s1, set);
	length = second_trim(s1, set);
	new_str = str_dup(s1, counter_str, length + 1);
	return (new_str);
}
