/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:45:57 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/16 15:49:15 by lbattest         ###   ########.fr       */
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

void	*free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (0);
}
