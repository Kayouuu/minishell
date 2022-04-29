/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/29 11:25:51 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clear_list(t_list_char **start)
{
	t_list_char	*tmp;
	int			i;

	i = 0;
	while ((*start) != NULL)
	{
		while ((*start)->redirection_file[i])
		{
			free((*start)->redirection_file[i]);
			i++;
		}
		free((*start)->redirection_file);
		free((*start)->type);
		free((*start)->content);
		tmp = *start;
		start = &(*start)->next;
		free(tmp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list_char	*command;
	t_list_char	*start;
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
		command = parsing(cmd);
		free(cmd);
		split_redirection(&command);
		replace_var_and_quote(&command);
		if (check_and_clean_parsing(&command) == 0)
			continue ;
		start = command;
		start_execution(&command, &env);
		clear_list(&start);
	}
	return (1);
}
