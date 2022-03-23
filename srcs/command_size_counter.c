/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_size_counter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:31:56 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/23 10:32:47 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_index	change(char c, t_index i)
{
	if (c == '"')
	{
		if (i.quote == '0')
			i.quote = '"';
		else if (i.quote == '"')
			i.quote = '0';
		else
			i.quotes += 1;
		i.d_quote += 1;
	}
	else if (c == '\'')
	{
		if (i.quote == '0')
			i.quote = '\'';
		else if (i.quote == '\'')
			i.quote = '0';
		else
			i.quotes += 1;
		i.s_quote += 1;
	}
	return (i);
}

int	count_size(char *cmd)
{
	t_index	index;
	char	first;
	int		i;

	index.s_quote = 0;
	index.d_quote = 0;
	index.quotes = 0;
	index.quote = '0';
	first = '0';
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' && first == '0')
			first = '"';
		else if (cmd[i] == '\'' && first == '0')
			first = '\'';
		index = change(cmd[i], index);
		i++;
	}
	if (index.s_quote % 2 == 1 && first == '\'')
		return (-1);
	if (index.d_quote % 2 == 1 && first == '"')
		return (-2);
	return (i + index.quotes);
}
