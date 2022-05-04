/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/15 10:31:45 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			return (0);
		add_history(cmd);
		command = parsing(cmd);
		free(cmd);
		split_redirection(&command);
		replace_var_and_quote(&command);
		printf("------------------------------------------\n");
		start = command;
		start_execution(&command, &env);
		lstclear_char(&start, free);
		// + free les tableaux de redirections
	}
	return (1);
}
