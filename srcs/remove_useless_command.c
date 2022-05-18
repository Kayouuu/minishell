/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_useless_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:43:45 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/18 12:06:42 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	remove_useless_command(t_list_char **cmd)
{
	t_list_char	*start;
	t_list_char	*current;
	int			to_free;

	start = *cmd;
	current = *cmd;
	to_free = 0;
	while (*cmd != NULL)
	{
		current = *cmd;
		(*cmd) = (*cmd)->next;
		if (to_free)
		{
			free(current);
			current = start;
			to_free = 0;
		}
	}
	*cmd = start;
}
