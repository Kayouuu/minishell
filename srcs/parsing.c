/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:04:02 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/16 17:04:39 by psaulnie         ###   ########.fr       */
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

static int	skip_whitespace(char *cmd, int i)
{
	while (cmd[i] == ' ' || cmd[i] == '\t'
		|| cmd[i] == '\n' || cmd[i] == '\v'
		|| cmd[i] == '\f' || cmd[i] == '\r')
		i++;
	return (i);
}

static int	is_useless(char *command)
{
	int	i;
	int	is_useless;

	i = 0;
	is_useless = 1;
	while (command[i])
	{
		if (!(command[i] == ' ' || command[i] == '\t' || command[i] == '\n'
				|| command[i] == '\n' || command[i] == '\v'
				|| command[i] == '\f' || command[i] == '\r'))
			is_useless = 0;
		i++;
	}
	return (is_useless);
}

static t_index	add_to_list(char *cmd, t_index index, t_list **list)
{
	char	*command;

	command = ft_stridup(cmd, index.i, index.j);
	if (!command)
	{
		free(cmd);
		ft_lstclear(list, free);
		ft_putstr_fd("Malloc error\n", 2);
		exit(0);
	}
	index.i += ft_strlen(command);
	if (!is_useless(command))
	{
		if (!ft_lstadd_back(list, ft_lstnew(command)))
		{
			free(cmd);
			ft_lstclear(list, free);
			ft_putstr_fd("Malloc error\n", 2);
			exit(0);
		}
		printf("Result = %s\n", command);
	}
	return (index);
}

static t_index	parsing_special_char(char *cmd, t_index index, t_list **list)
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

t_list	*parsing(char *cmd)
{
	t_list	*list;
	t_index	index;

	index.i = 0;
	while (cmd[index.i])
	{
		index.j = index.i;
		while (cmd[index.j])
		{
			if (cmd[index.j] == '|' || cmd[index.j] == '>'
				|| cmd[index.j] == '<' || cmd[index.j] == ';')
			{
				index = parsing_special_char(cmd, index, &list);
				break ;
			}
			index.j++;
		}
		index.i = skip_whitespace(cmd, index.i);
		index = add_to_list(cmd, index, &list);
		if (cmd[index.i + 1])
			index.i++;
	}
	return (list);
}
