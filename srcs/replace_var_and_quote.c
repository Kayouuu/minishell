/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_and_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:41:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/22 16:01:55 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*replace_env_var(t_list_char **start, char *cmd, char *envp[])
{
	char	*new_command;
	int		can_replace;
	char	*var_name;
	int		i;
	int		j;

	i = 0;
	can_replace = 1;
	new_command = NULL;
	(void)envp;
	while (cmd[i] != '\0')
	{
		j = i;
		while (cmd[j] != '\0' && (cmd[j] != '$' || can_replace == 0))
		{
			if (cmd[j] == '\'')
				can_replace ^= 1;
			j++;
		}
		if (i != j)
		{
			new_command = ft_strjoin_gnl(new_command, ft_stridup(cmd, i, j));
			if (!new_command)
			{
				lstclear_char(start, free);
				exit (0);
			}
		}
		i = j;
		if (cmd[i] == '$' && can_replace)
		{
			i++;
			while (cmd[i] && ft_isalnum(cmd[i]))
				i++;
			var_name = ft_stridup(cmd, j + 1, i);
			new_command = ft_strjoin_gnl(new_command, getenv(var_name));
			if (!new_command)
			{
				lstclear_char(start, free);
				exit (0);
			}
		}
		else if (cmd[i])
			i++;
	}
	new_command = ft_strjoin_gnl(new_command, "\0");
	free(cmd);
	return (new_command);
}

t_list_char	*replace_var_and_quote(t_list_char *cmd, char *envp[])
{
	t_list_char	**start;
	int			size;

	start = &cmd;
	while (cmd != NULL)
	{
		size = count_size(cmd->content);
		if (size == -1)
			cmd->content = dquote(cmd->content, 0);
		if (size == -2)
			cmd->content = dquote(cmd->content, 1);
		printf("-------------Replace environnement var--------------\n");
		cmd->content = replace_env_var(start, cmd->content, envp);
		printf("[%s]\n", cmd->content);
		printf("-------------Dquote + Remove quote-----------------\n");
		while (size < 0)
		{
			size = count_size(cmd->content);
			if (size == -1)
				cmd->content = dquote(cmd->content, 0);
			if (size == -2)
				cmd->content = dquote(cmd->content, 1);
		}
		cmd->content = remove_quote(start, cmd->content);
		printf("[%s]\n", cmd->content);
		cmd = cmd->next;
	}
	return (*start);
}
