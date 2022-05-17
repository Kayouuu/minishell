/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_clean_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:38:20 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/17 15:38:20 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_parsing(t_list_char **start, t_list_char **cmd)
{
	int	i;

	i = 0;
	while ((*cmd)->type[i] != -1)
	{
		if ((*cmd)->type[i] == 0)
		{
			clear_list(start);
			ft_putendl_fd("minishell: parse error", 2);
			return (1);
		}
		if ((*cmd)->redirection_file[i] == NULL
			|| (*cmd)->redirection_file[i][0] == '\0')
		{
			clear_list(start);
			ft_putendl_fd("minishell: parse error", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_and_clean_parsing(t_list_char **cmd)
{
	t_list_char		*start;
	char			*tmp;

	start = *cmd;
	while (*cmd != NULL)
	{
		tmp = (*cmd)->content;
		(*cmd)->content = ft_strtrim((*cmd)->content, " \t\n\b\f");
		free(tmp);
		if (check_parsing(&start, cmd) == 1)
			return (0);
		dprintf(2, "%s\n", (*cmd)->content);
		(*cmd) = (*cmd)->next;
	}
	remove_useless_command(&start);
	*cmd = start;
	return (1);
}
