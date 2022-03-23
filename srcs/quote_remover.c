/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:31:56 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/23 11:14:21 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	set_last_quote(char c, t_index index)
{
	if (index.last_quote == '0')
	{
		if (c == '"')
			index.last_quote = '"';
		else if (c == '\'')
			index.last_quote = '\'';
		if (index.last_quote != '0')
			index.last_quote_index = index.i;
	}
	return (index.last_quote);
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
		index.last_quote = set_last_quote(cmd[index.i], index);
		if ((cmd[index.i] != '"' || index.last_quote != '"')
			&& (cmd[index.i] != '\'' || index.last_quote != '\''))
		{
			new_cmd[index.j] = cmd[index.i];
			index.j++;
		}
		else if (((cmd[index.i] == '"' && index.last_quote != '"')
				|| (cmd[index.i] == '\'' && index.last_quote != '\''))
			&& (index.last_quote == cmd[index.i]))
		{
			new_cmd[index.j] = cmd[index.i];
			index.j++;
		}
		if (index.last_quote == cmd[index.i]
			&& index.last_quote_index != index.i)
			index.last_quote = '0';
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
	return (new_cmd);
}
