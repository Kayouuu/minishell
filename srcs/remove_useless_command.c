/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_useless_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:43:45 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/07 10:11:47 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static char	**edit_array(t_list_char **start, char **cmd, t_list_char **command)
// {
	
// }

void	remove_useless_command(t_list_char **cmd)
{
	t_list_char	*start;
	t_list_char	*current;
	t_list_char *node;
	int			to_free;

	start = *cmd;
	current = *cmd;
	node = start;
	to_free = 0;
	while (*cmd != NULL)
	{
		if (to_free)
		{
			to_free = 0;
			current = start;
		}
		// edit_array(&start, (*cmd)->content, cmd);
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
		}
	}
	*cmd = start;
}
