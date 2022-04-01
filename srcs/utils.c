/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:45:57 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/01 12:41:42 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_error_msg(char *str)
{
	ft_putendl_fd(str, 2);
	exit (1);
}

void	error(int i, char *str)
{
	if (i == 0)
		perror("minishell");
	else if (i == 1)
		ft_putendl_fd(str, 2);
	exit(1);
}
