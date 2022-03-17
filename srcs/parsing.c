/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:04:02 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/17 11:52:17 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	Parsing function : parse the command sent
	If there's is no special characters (|, >, <, ;), it will just create one
	link. Else, the linked list will have many more links. Example :
	-minishell > echo "'hi'" > d | xargs;
	- [echo "'hi'"] [>] [d] [|] [xargs]
*/

static t_index	add_to_list(char *cmd, t_index index, t_list_char **list)
{
	char	*command;

	command = ft_stridup(cmd, index.i, index.j);
	if (!command)
	{
		free(cmd);
		lstclear_char(list, free);
		ft_putstr_fd("Malloc error\n", 2);
		exit(0);
	}
	index.i += ft_strlen(command);
	if (!is_useless(command))
	{
		if (!lstadd_back_char(list, lstnew_char(command)))
		{
			free(cmd);
			lstclear_char(list, free);
			ft_putstr_fd("Malloc error\n", 2);
			exit(0);
		}
		printf("Result = %s\n", command);
	}
	return (index);
}

static t_index	parsing_special_char(char *cmd, t_index index,
	t_list_char **list)
{
	if (index.i != 0)
		index.i--;
	index.i = skip_whitespace(cmd, index.i);
	if (index.j - index.i != 0)
		index = add_to_list(cmd, index, list);
	while (cmd[index.j] && cmd[index.j] != '|' && cmd[index.j] != '\''
		&& cmd[index.j] != '"' && cmd[index.j] != '>' && cmd[index.j] != ';')
		index.j++;
	return (index);
}

static t_index	parsing_loop(char *cmd, t_index index, t_list_char **list)
{
	index.j = index.i;
	while (cmd[index.j])
	{
		if (cmd[index.j] == '\'')
			index.s_quote ^= 1;
		if (cmd[index.j] == '"')
			index.d_quote ^= 1;
		if ((cmd[index.j] == '|' || cmd[index.j] == '>'
				|| cmd[index.j] == '<' || cmd[index.j] == ';')
			&& (index.d_quote == 0 && index.s_quote == 0))
		{
			index = parsing_special_char(cmd, index, list);
			break ;
		}
		index.j++;
	}
	return (index);
}

static t_index	parsing_end(char *cmd, t_index index, t_list_char **list)
{
	index.i = skip_whitespace(cmd, index.i);
	index = add_to_list(cmd, index, list);
	if ((cmd[index.i - 1] == '|' || cmd[index.i - 1] == '>'
			|| cmd[index.i - 1] == '<' || cmd[index.i - 1] == ';')
		&& !(cmd[index.i] == ' ' || cmd[index.i] == '\t'
			|| cmd[index.i] == '\n' || cmd[index.i] == '\n'
			|| cmd[index.i] == '\v' || cmd[index.i] == '\f'
			|| cmd[index.i] == '\r'))
		index.i--;
	if (cmd[index.i + 1])
		index.i++;
	return (index);
}

t_list_char	*parsing(char *cmd)
{
	t_list_char	*list;
	t_index		index;

	index.i = 0;
	index.s_quote = 0;
	index.d_quote = 0;
	list = NULL;
	while (cmd[index.i])
	{
		index = parsing_loop(cmd, index, &list);
		index = parsing_end(cmd, index, &list);
	}
	return (list);
}
