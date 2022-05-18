/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:23:21 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/18 11:55:04 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// MALLOC A PROTEGER

int	ft_iswhitespace(char c)
{
	return ((c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f') && c);
}

static char	**put_in_char_array(t_list_char *cmd, t_list_char **start)
{
	char		**commands;
	char		*tmp;
	int			i;

	i = 0;
	commands = malloc(sizeof(char *) * (lstsize_char(cmd) + 1));
	if (!commands)
		exit (0);
	while (cmd != NULL)
	{
		if (!is_useless(cmd->content))
		{
			tmp = cmd->content;
			commands[i] = remove_quote(start, cmd->content);
			i++;
		}
		cmd = cmd->next;
	}
	commands[i] = NULL;
	return (commands);
}

static char	set_quote(char *cmd, t_index var)
{
	if (cmd[var.j] == var.quote)
		var.quote = '0';
	if (cmd[var.j] == '\'' && var.quote == '0')
		var.quote = '\'';
	else if (cmd[var.j] == '"' && var.quote == '0')
		var.quote = '"';
	return (var.quote);
}

static t_list_char	*command_splitter_loop(char *cmd, t_index var,
	t_list_char *command)
{
	char	*str;

	while (cmd && cmd[var.i])
	{
		var.j = var.i;
		while (cmd[var.j])
		{
			var.quote = set_quote(cmd, var);
			if (ft_iswhitespace(cmd[var.j]) && var.quote == '0')
				break ;
			var.j++;
		}
		str = ft_stridup(cmd, var.i, var.j);
		if (!str)
			exit (0);
		lstadd_back_char(&command, lstnew_char(str));
		if (!command)
			exit (0);
		var.i = var.j;
		if (cmd[var.i])
			var.i++;
	}
	return (command);
}

char	**command_splitter(char *cmd, t_list_char **start)
{
	t_list_char	*command;
	char		**new_cmd;
	t_index		var;

	var.i = 0;
	var.quote = '0';
	command = NULL;
	command = command_splitter_loop(cmd, var, command);
	new_cmd = put_in_char_array(command, start);
	lstclear_char(&command, NULL);
	return (new_cmd);
}
