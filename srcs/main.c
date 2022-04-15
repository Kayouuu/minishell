/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/15 17:14:25 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	clear_list(t_list_char **start)
{
	t_list_char	*tmp;

	while ((*start) != NULL)
	{
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
	char		*cmd;
	t_env		env;

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
		start = command;
		start_execution(&command, &env);
		clear_list(&start);
	}
	return (1);
}
