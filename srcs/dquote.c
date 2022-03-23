/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:34:28 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/23 10:02:49 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*dquote(char *cmd, int arg)
{
	char	*new_command;
	char	*command;
	t_index	index;
	char	quote;
	int		is_good;

	index.s_quote = 0;
	index.d_quote = 0;
	is_good = 0;
	quote = '0';
	if (arg == 0)
		quote = '\'';
	else if (arg == 1)
		quote = '"';
	new_command = NULL;
	new_command = ft_strjoin_gnl(new_command, "\n");
	if (!new_command)
		exit(0);
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
			exit(0);
		}
		free(command);
		if (is_good)
			break ;
		new_command = ft_strjoin_gnl(new_command, "\n");
		if (!new_command)
			exit(0);
	}
	cmd = ft_strjoin_gnl(cmd, new_command);
	if (!cmd)
	{
		free(new_command);
		exit(0);
	}
	free(new_command);
	return (cmd);
}
