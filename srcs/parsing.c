/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:04:02 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/16 16:19:36 by psaulnie         ###   ########.fr       */
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

static void	free_and_exit(char *cmd, t_list *list)
{
	free(cmd);
	ft_lstclear(&list, free);
	ft_putstr_fd("Malloc error\n", 2);
	exit(0);
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

t_list	*parsing(char *cmd)
{
	t_list	*list;
	char	*command;
	int		state;
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = i;
		state = 0;
		while (cmd[j])
		{
			if (cmd[j] == '|' || cmd[j] == '>'
				|| cmd[j] == '<' || cmd[j] == ';')
			{
				if (i != 0)
					i--;
				while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\n'
					|| cmd[i] == '\v' || cmd[i] == '\f' || cmd[i] == '\r')
					i++;
				state = 1;
				if (j - i != 0)
				{
					command = ft_stridup(cmd, i, j);
					if (!command)
						free_and_exit(cmd, list);
					i += ft_strlen(command);
					if (!is_useless(command))
						if (!ft_lstadd_back(&list, ft_lstnew(command)))
							free_and_exit(cmd, list);
				}
				while (cmd[j] && cmd[j] != '|' && cmd[j] != '\''
					&& cmd[j] != '"' && cmd[j] != '>' && cmd[j] != ';')
					j++;
				break ;
			}
			j++;
		}
		while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\n'
			|| cmd[i] == '\v' || cmd[i] == '\f' || cmd[i] == '\r')
			i++;
		command = ft_stridup(cmd, i, j);
		if (!command)
			free_and_exit(cmd, list);
		i += ft_strlen(command);
		if (!is_useless(command))
			if (!ft_lstadd_back(&list, ft_lstnew(command)))
				free_and_exit(cmd, list);
		if (cmd[i + 1])
			i++;
	}
	printf("%s\n", list->content);
	return (list);
}
