/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:11:59 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/04 11:54:22 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*splitter(t_list_char **start, char *cmd)
{
	t_index	var;

	var.i = 0;
	var.s_quote = 0;
	var.d_quote = 0;
	while (cmd[var.i] && (var.s_quote == 0 && var.d_quote == 0)
		&& (cmd[var.i] == '<' || cmd[var.i] == '>'))
	{
		if (cmd[var.i] == '\'')
			var.s_quote ^= 1;
		if (cmd[var.i] == '"')
			var.d_quote ^= 1;
		var.i++;
	}
	var.j = var.i;
	while (cmd[var.j])
	{
		
	}
}

void	split_redirection(t_list_char **cmd)
{
	t_list_char	*start;

	start = *cmd;
	while (*cmd != NULL)
	{
		(*cmd)->content = splitter(&start, (*cmd)->content);
		(*cmd) = (*cmd)->next;
	}
	*cmd = start;
}
