/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:31:56 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/22 15:56:51 by psaulnie         ###   ########.fr       */
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
	int		i;

	index.s_quote = 0;
	index.d_quote = 0;
	index.quotes = 0;
	index.quote = '0';
	i = 0;
	while (cmd[i])
	{
		index = change(cmd[i], index);
		i++;
	}
	if (index.s_quote % 2 == 1)
		return (-1);
	if (index.d_quote % 2 == 1)
		return (-2);
	return (i + index.quotes);
}

char	*remove_quote(t_list_char **start, char *cmd)
{
	t_index	index;
	char	*new_cmd;
	char	last_quote;
	int		last_quote_index;
	int		size;

	size = count_size(cmd);
	new_cmd = malloc(sizeof(char) * (size + 1));
	if (!new_cmd)
	{
		lstclear_char(start, free);
		ft_putendl_fd("Malloc error", 2);
		exit(0);
	}
	index.i = 0;
	index.j = 0;
	index.d_quote = 0;
	index.s_quote = 0;
	last_quote = '0';
	last_quote_index = -1;
	while (cmd[index.i])
	{
		if (last_quote == '0')
		{
			if (cmd[index.i] == '"')
				last_quote = '"';
			else if (cmd[index.i] == '\'')
				last_quote = '\'';
			if (last_quote != '0')
				last_quote_index = index.i;
		}
		if ((cmd[index.i] != '"' || last_quote != '"')
			&& (cmd[index.i] != '\'' || last_quote != '\''))
		{
			new_cmd[index.j] = cmd[index.i];
			index.j++;
		}
		else if (((cmd[index.i] == '"' && last_quote != '"')
				|| (cmd[index.i] == '\'' && last_quote != '\''))
			&& (last_quote == cmd[index.i]))
		{
			new_cmd[index.j] = cmd[index.i];
			index.j++;
		}
		if (last_quote == cmd[index.i] && last_quote_index != index.i)
			last_quote = '0';
		index.i++;
	}
	new_cmd[index.j] = '\0';
	return (new_cmd);
}
