/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_size_counter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:31:56 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/01 16:20:51 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_index	check(char *cmd, t_index index)
{
	if ((index.j == 2 && cmd[index.i] == '"')
		|| (index.j == 2 && cmd[index.i] == '\''))
	{
		index.last_quote = '0';
		index.j = 0;
	}
	if (cmd[index.i] == '"' && index.last_quote != '\'')
	{
		index.last_quote = '"';
		index.j += 1;
	}
	else if (cmd[index.i] == '\'' && index.last_quote != '"')
	{
		index.last_quote = '\'';
		index.j += 1;
	}
	if (cmd[index.i] == '\'' && cmd[index.i] == '"')
		index.j += 1;
	return (index);
}

static t_index	change(char c, t_index i)
{
	if (c == '"' && i.last_quote != '\'')
	{
		if (i.quote == '0')
			i.quote = '"';
		else if (i.quote == '"')
			i.quote = '0';
		else if (i.last_quote != '\'')
			i.quotes += 1;
		i.d_quote += 1;
	}
	else if (c == '\'' && i.last_quote != '"')
	{
		if (i.quote == '0')
			i.quote = '\'';
		else if (i.quote == '\'')
			i.quote = '0';
		else if (i.last_quote != '"')
			i.quotes += 1;
		i.s_quote += 1;
	}
	return (i);
}

int	count_size(char *cmd)
{
	t_index	index;

	index.s_quote = 0;
	index.d_quote = 0;
	index.quotes = 0;
	index.quote = '0';
	index.last_quote = '0';
	index.i = 0;
	index.j = 0;
	while (cmd[index.i])
	{
		index = check(cmd, index);
		index = change(cmd[index.i], index);
		index.i++;
	}
	return (index.i + index.quotes);
}
