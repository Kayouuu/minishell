/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_and_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:41:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/22 12:03:44 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*replace_env_var(t_list_char **start, char *cmd, char *envp[])
{
	t_list_char	*env_var;
	char		*var_name;
	char		*new_cmd;
	int			can_replace;
	int			i;
	int			j;

	env_var = NULL;
	can_replace = 1;
	i = 0;
	new_cmd = NULL;
	(void)envp;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			can_replace ^= 1;
		if (cmd[i] == '$' && can_replace)
		{
			j = i + 1;
			while (cmd[j] && ft_isalnum(cmd[j]))
				j++;
			var_name = ft_stridup(cmd, i + 1, j);
			if (!var_name)
			{
				// protection malloc
				exit(0);
			}
			if (!lstadd_back_char(&env_var, lstnew_char(getenv(var_name))))
			{
				// protection malloc
				exit(0);
			}
			printf("--->[%s]\n", getenv(var_name));
			free(var_name);
		}
		i++;
	}
	start = NULL;
	return (new_cmd);
}

t_list_char	*replace_var_and_quote(t_list_char *cmd, char *envp[])
{
	t_list_char	**start;
	int			size;

	start = &cmd;
	while (cmd != NULL)
	{
		printf("-------------Dquote + Remove quote-----------------\n");
		size = count_size(cmd->content);
		if (size == -1)
			cmd->content = dquote(cmd->content, 0);
		if (size == -2)
			cmd->content = dquote(cmd->content, 1);
		cmd->content = remove_quote(start, cmd->content);
		printf("[%s]\n", cmd->content);
		printf("-------------Replace environnement var--------------\n");
		cmd->content = replace_env_var(start, cmd->content, envp);
		cmd = cmd->next;
	}
	return (*start);
}
