/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/04 14:13:34 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clear_list(t_list_char **start)
{
	t_list_char	*tmp;
	int			i;

	while (*start != 0)
	{
		tmp = (*start)->next;
		i = 0;
		while ((*start)->redirection_file[i] != NULL)
		{
			free((*start)->redirection_file[i]);
			i++;
		}
		free((*start)->type);
		free((*start)->content);
		free((*start)->redirection_file);
		free((*start));
		(*start) = tmp;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list_char	*command;
	t_list_char	**start;
	t_env		env;
	char		*cmd;

	(void)argc;
	(void)argv;
	env.envp = envp;
	while (1)
	{
		cmd = readline("\033[0;36mminishell> \033[0;37m");
		if (!cmd)
			exit (0);
		add_history(cmd);
		cmd = replace_env_var(cmd);
		command = parsing(cmd);
		free(cmd);
		split_redirection(&command);
		if (check_and_clean_parsing(&command) == 0)
			continue ;
		start = &command;
		start_execution(&command, &env);
		clear_list(start);
	}
	return (1);
}
