/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:13:38 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/10 08:53:50 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Write the string s in the file fd										  */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	counter;

	if (s == 0 || fd == 0)
		return ;
	counter = 0;
	while (s[counter])
	{
		write(fd, &s[counter], 1);
		counter++;
	}
}
