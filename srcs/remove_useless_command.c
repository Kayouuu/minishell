/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_useless_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:43:45 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/07 11:35:39 by psaulnie         ###   ########.fr       */
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
		if (is_useless((*cmd)->content) || cmd[0] == '\0')
		{
			free((*cmd)->content);
			current->next = (*cmd)->next;
			to_free = 1;
		}
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
