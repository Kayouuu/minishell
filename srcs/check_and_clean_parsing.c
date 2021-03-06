/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_clean_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:38:20 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/25 11:44:23 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_parsing(t_list_char **start, t_list_char **cmd)
{
	int	i;

	i = 0;
	if ((*cmd)->content && (*cmd)->content[0] == '|' && (*cmd)->next
		&& (*cmd)->next->content && (*cmd)->next->content[0] == '|')
	{
		clear_list(start);
		ft_putendl_fd("minishell: parse error near '|'", 2);
		return (1);
	}
	while ((*cmd)->type[i] != -1)
	{
		if ((*cmd)->type[i] == 0 || (*cmd)->redirection_file[i][0] == '\0')
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
	if ((*cmd) && (*cmd)->content && (*cmd)->content[0] == '|')
	{
		ft_putendl_fd("minishell: unexpected token '|'", 2);
		clear_list(&start);
		return (0);
	}
	while (*cmd != NULL)
	{
		tmp = (*cmd)->content;
		(*cmd)->content = ft_strtrim((*cmd)->content, " \t\n\b\f");
		free(tmp);
		if (check_parsing(&start, cmd) == 1)
			return (0);
		(*cmd) = (*cmd)->next;
	}
	remove_useless_command(&start);
	*cmd = start;
	return (1);
}
