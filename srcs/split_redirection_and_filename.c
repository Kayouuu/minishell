/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection_and_filename.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:44:35 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/06 15:07:56 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	
	If we have "> test" then it will edit the array to have ">" " test"
	Works for ">", "<", ">>", "<<"
*/

static void	error_case(char *new_str, char *new_link_str, t_list_char **start)
{
	free(new_str);
	free(new_link_str);
	lstclear_char(start, free);
	exit_error_msg("Malloc error");
}

static void	add_next(t_list_char **next_link, t_list_char **start,
		t_list_char **command)
{
	t_list_char	*new_link;
	t_index		var;
	char		*next;
	char		*cmd;

	cmd = (*next_link)->content;
	if (!cmd)
		return ;
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
	next = ft_stridup(cmd, 0, var.i);
	if (!next)
	{
		lstclear_char(start, free);
		exit_error_msg("Malloc error");
	}
	var.i = skip_whitespace(cmd, var.i);
	new_link = lstnew_char(next);
	if (!new_link)
	{
		free(next);
		lstclear_char(start, free);
		exit_error_msg("Malloc error");
	}
	(*next_link)->content = ft_strcut((*next_link)->content, 0, var.i - 1);
	if (!(*next_link)->content)
	{
		(*next_link)->content = NULL;
		lstclear_char(start, free);
		free(next);
		exit_error_msg("Malloc error");
	}
	(*command)->next = new_link;
	new_link->next = *next_link;
	(*start) = (*start)->next;
}

static char	*redirection_split(char *cmd, t_list_char **start)
{
	char	c[2];
	char	*new_str;

	c[0] = cmd[0];
	c[1] = '\0';
	if (cmd[1] == cmd[0])
	{
		new_str = ft_strjoin(c, c);
		if (!new_str)
		{
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
	}
	else
	{
		new_str = ft_strdup(c);
		if (!new_str)
		{
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
	}
	return (new_str);
}

static char	*splitter(t_list_char **start, char *cmd, t_list_char **command)
{
	t_index		var;
	t_list_char	*new_link;
	char		*new_link_str;
	char		*new_str;
	char		c;

	if (cmd[0] != '<' && cmd[0] != '>')
		return (cmd);
	c = cmd[0];
	new_str = redirection_split(cmd, start);
	var.i = ft_strlen (new_str);
	new_link_str = ft_strcut(cmd, 0, var.i - 1);
	if (!new_link_str)
	{
		free(new_str);
		lstclear_char(start, free);
		exit_error_msg("Malloc error");
	}
	new_link = lstnew_char(new_link_str);
	if (!new_link)
		error_case(new_str, new_link_str, start);
	new_link->next = (*command)->next;
	(*command)->next = new_link;
	add_next(&new_link, start, command);
	return (new_str);
}

void	split_redirection_and_filename(t_list_char **cmd)
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
