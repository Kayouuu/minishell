/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:23:21 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/04 12:00:53 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// MALLOC A PROTEGER

int	ft_iswhitespace(char c)
{
	return ((c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f') && c);
}

static char	**put_in_char_array(t_list_char *cmd)
{
	char		**commands;
	int			i;

	i = 0;
	commands = malloc(sizeof(char *) * (lstsize_char(cmd) + 1));
	if (!commands)
		exit (0);
	while (cmd != NULL)
	{
		commands[i] = cmd->content;
		cmd = cmd->next;
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

char	**command_splitter(char *cmd)
{
	t_list_char	*command;
	char		**new_cmd;
	char		*str;
	t_index		var;

	var.i = 0;
	command = NULL;
	while (cmd[var.i])
	{
		var.j = var.i;
		while (cmd[var.j] && ft_iswhitespace(cmd[var.j]) == 0)
			var.j++;
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
	new_cmd = put_in_char_array(command);
	lstclear_char(&command, free);
	return (new_cmd);
}
