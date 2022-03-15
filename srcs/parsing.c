/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:04:02 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/15 19:07:29 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*parsing(char *cmd, char *envp[])
{
	t_list	*list;
	char	*command;
	int		state;
	int		i;
	int		j;
	int		k;

	(void)envp;
	i = 0;
	while (cmd[i])
	{
		j = i;
		state = 0;
		while (cmd[j])
		{
			if (cmd[j] == '$' || cmd[j] == '|' || cmd[j] == '>'
				|| cmd[j] == '<' || cmd[j] == '\'' || cmd[j] == '"')
			{
				state = 1;
				k = 0;
				printf("A\n");
				while (cmd[j] && cmd[j] != '|' && cmd[j] != '\''
					&& cmd[j] != '"' && cmd[j] != '>')
					j++;
				break ;
			}
			j++;
		}
		if (state == 1)
		{
			k = 0;
			command = malloc(sizeof(char) * (j + 1));
			while (i < j)
			{
				command[k] = cmd[i];
				i++;
				k++;
			}
			command[k] = '\0';
			printf("%s\n", command);
		}
		else
		{
			command = malloc(sizeof(char) * (j - i + 1));
			if (!command)
			{
				// free
				exit(0);
			}
			k = 0;
			while (i < j)
			{
				command[k] = cmd[i];
				i++;
				k++;
			}
			command[k] = '\0';
			list = ft_lstnew(&command);
			printf("%s\n", command);
		}
		i++;
	}
	return (list);
}
