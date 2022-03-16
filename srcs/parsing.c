/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:04:02 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/16 13:56:19 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	Parsing function :
*/

static void	free_and_exit(char *cmd, t_list *list)
{
	free(cmd);
	ft_lstclear(&list, free);
	exit(0);
}

char	*ft_stridup(char *str, int start, int end)
{
	char	*returned_str;
	int		i;

	i = 0;
	if (start == end)
		end++;
	returned_str = malloc(sizeof(char) * (end - start + 1));
	if (!returned_str)
		return (NULL);
	while (str[start] && start < end)
	{
		returned_str[i] = str[start];
		i++;
		start++;
	}
	returned_str[i] = '\0';
	return (returned_str);
}

int		is_useless(char *command)
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

t_list	*parsing(char *cmd, char *envp[])
{
	t_list	*list;
	char	*command;
	int		state;
	int		i;
	int		j;

	(void)envp;
	i = 0;
	list = ft_lstnew(NULL);
	if (!list)
	{
		free(cmd);
		exit(0);
	}
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
					{
						printf("Result = %s\n", command);
						ft_lstadd_front(&list, ft_lstnew(command));
					}
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
		if (state == 1)
		{
			command = ft_stridup(cmd, i, j);
			if (!command)
				free_and_exit(cmd, list);
			i += ft_strlen(command);
			if (!is_useless(command))
			{
				printf("Result = %s\n", command);
				ft_lstadd_front(&list, ft_lstnew(command));
			}
		}
		else
		{
			command = ft_stridup(cmd, i, j);
			if (!command)
				free_and_exit(cmd, list);
			i += ft_strlen(command);
			if (!is_useless(command))
			{
				printf("Result = %s\n", command);
				ft_lstadd_front(&list, ft_lstnew(command));
			}
		}
		if (cmd[i + 1])
			i++;
		free(command);
	}
	// printf("%s\n", (char *)list->content);
	return (list);
}
