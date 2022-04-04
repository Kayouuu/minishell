/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:11:59 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/04 15:20:47 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*splitter(t_list_char **start, char *cmd, t_list_char **command)
{
	t_list_char	*new_link;
	t_index		var;
	char		*str;

	var.i = 0;
	var.quote = '0';
	var.quotes = 0;
	(void)command;
	while (cmd[var.i] && (cmd[var.i] != '<' && cmd[var.i] != '>'
			&& var.quotes % 2 == 0))
	{
		if (cmd[var.i] == '\'' && (var.quotes == '0'))
			var.quote = '\'';
		if (cmd[var.i] == '"' && (var.quotes == '0'))
			var.quote = '"';
		if (cmd[var.i] == var.quotes)
			var.quotes++;
		if (var.quotes == 2)
		{
			var.quote = '0';
			var.quotes = 0;
		}
		var.i++;
	}
	var.j = var.i;
	while (cmd[var.j] && !ft_iswhitespace(cmd[var.j]))
		var.j++;
	if (cmd[var.j])
	{
		var.j++;
		while (cmd[var.j] && !ft_iswhitespace(cmd[var.j]))
			var.j++;
	}
	if (var.j != var.i && var.i != 0 && var.j != (int)ft_strlen(cmd) - 1)
	{
		str = ft_stridup(cmd, var.i, var.j);
		if (!str)
		{
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
		//printf("[%s]\n", str);
		new_link = lstnew_char(str);
		if (!new_link)
		{
			free(str);
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
		new_link->next = (*command)->next;
		(*command)->next = new_link;
	}
	return (cmd);
}

void	split_redirection(t_list_char **cmd)
{
	t_list_char	*start;

	start = *cmd;
	while (*cmd != NULL)
	{
		(*cmd)->content = splitter(&start, (*cmd)->content, cmd);
		(*cmd) = (*cmd)->next;
	}
	*cmd = start;
}
