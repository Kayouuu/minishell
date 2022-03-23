/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:34:28 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/23 13:35:52 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	Dquote function : loop a readline until it find the right quote
*/

static char	*dquote_loop(char *new_command, char quote, t_index index)
{
	char	*command;
	int		is_good;

	is_good = 0;
	while (1)
	{
		command = readline("> ");
		index.i = 0;
		while (command[index.i])
			if (command[index.i++] == quote)
				is_good ^= 1;
		new_command = ft_strjoin_gnl(new_command, command);
		if (!new_command)
		{
			free(command);
			exit_error_msg("Malloc error");
		}
		free(command);
		if (is_good)
			break ;
		new_command = ft_strjoin_gnl(new_command, "\n");
		if (!new_command)
			exit_error_msg("Malloc error");
	}
	return (new_command);
}

char	*dquote(char *cmd, int arg)
{
	char	*new_command;
	t_index	index;

	index.s_quote = 0;
	index.d_quote = 0;
	index.quote = '0';
	if (arg == 0)
		index.quote = '\'';
	else if (arg == 1)
		index.quote = '"';
	new_command = NULL;
	new_command = ft_strjoin_gnl(new_command, "\n");
	if (!new_command)
		exit_error_msg("Malloc error");
	new_command = dquote_loop(new_command, index.quote, index);
	cmd = ft_strjoin_gnl(cmd, new_command);
	if (!cmd)
	{
		free(new_command);
		exit_error_msg("Malloc error");
	}
	free(new_command);
	return (cmd);
}
