/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:24:57 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/10 08:54:05 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Write the string s in the file fd and add a newline						  */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	counter;

	counter = 0;
	if (s == 0 || fd == 0)
		return ;
	while (s[counter])
	{
		write(fd, &s[counter], 1);
		counter++;
	}
	write(fd, "\n", 1);
}
