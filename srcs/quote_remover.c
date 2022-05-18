/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:31:56 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/18 15:14:33 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	Remove_quote function : work like a strdup but pass the right quotes
*/

static int	have_next_quote(char *cmd, int i)
{
	char	quote;

	quote = cmd[i];
	i++;
	while (cmd[i])
	{
		if (cmd[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

static t_index	remove_quote_init(void)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	index.d_quote = 0;
	index.s_quote = 0;
	index.last_quote = '0';
	index.last_quote_index = -1;
	return (index);
}

static char	*remove_quote_loop(char *new_cmd, t_index index, char *cmd)
{
	while (cmd[index.i])
	{
		if (cmd[index.i] == '"' || cmd[index.i] == '\'')
		{
			if (index.last_quote == '0')
			{
				index.last_quote = cmd[index.i];
				if (!have_next_quote(cmd, index.i))
					new_cmd[index.j++] = cmd[index.i];
				while (cmd[++index.i] && cmd[index.i] != index.last_quote)
					new_cmd[index.j++] = cmd[index.i];
				index.last_quote = '0';
			}
		}
		else
		{
			new_cmd[index.j] = cmd[index.i];
			index.j++;
		}
		if (cmd[index.i])
			index.i++;
	}
	new_cmd[index.j] = '\0';
	return (new_cmd);
}

char	*remove_quote(t_list_char **start, char *cmd)
{
	t_index	index;
	char	*new_cmd;
	int		size;

	size = count_size(cmd);
	new_cmd = malloc(sizeof(char) * (size + 1));
	if (!new_cmd)
	{
		lstclear_char(start, free);
		exit_error_msg("Malloc error");
	}
	index = remove_quote_init();
	new_cmd = remove_quote_loop(new_cmd, index, cmd);
	free(cmd);
	return (new_cmd);
}
