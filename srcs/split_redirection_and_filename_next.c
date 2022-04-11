/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection_and_filename_next.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:27:41 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/11 11:46:21 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	This part is meant to add to the list the next command of the function
	after : [echo a b] [>] [test echo a] => [echo a b] [>] [test] [echo a b]
*/
static void	error_handler(t_list_char **start)
{
	lstclear_char(start, free);
	exit_error_msg("Malloc error");
}

static void	link_list_correctly(t_list_char **command, t_list_char *new_link,
			t_list_char **next_link)
{
	(*command)->next = new_link;
	new_link->next = *next_link;
}

static int	skipper(char *cmd)
{
	t_index	var;

	var.i = 0;
	var.i = skip_whitespace(cmd, var.i);
	while (cmd[var.i] && !ft_iswhitespace(cmd[var.i]) && var.quotes % 2 == 0)
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
	return (var.i);
}

void	add_next(t_list_char **next_link, t_list_char **start,
		t_list_char **command)
{
	t_list_char	*new_link;
	t_index		var;
	char		*next;
	char		*cmd;

	cmd = (*next_link)->content;
	if (!cmd || !cmd[skipper(&cmd[1])])
		return ;
	var.i = skipper(cmd);
	next = ft_stridup(cmd, 0, var.i);
	if (!next)
		error_handler(start);
	var.i = skip_whitespace(cmd, var.i);
	new_link = lstnew_char(next);
	(*next_link)->content = ft_strcut((*next_link)->content, 0, var.i - 1);
	if (!new_link)
	{
		free(next);
		lstclear_char(&new_link, free);
		error_handler(start);
	}
	link_list_correctly(command, new_link, next_link);
}
