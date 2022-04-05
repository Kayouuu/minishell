/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection_and_filename.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:44:35 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/05 14:32:58 by psaulnie         ###   ########.fr       */
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

static char	*redirection_split(char *cmd, t_list_char **start)
{
	char	c;
	char	*new_str;

	c = cmd[0];
	if (cmd[1] == cmd[0])
	{
		new_str = ft_strjoin(&c, &c);
		if (!new_str)
		{
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
	}
	else
	{
		new_str = ft_strdup(&c);
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
	t_list_char	*new_link;
	t_index		var;
	char		*new_str;
	char		*new_link_str;
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
