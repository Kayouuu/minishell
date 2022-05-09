/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/06 13:51:16 by lbattest         ###   ########.fr       */
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

void	signalhandler(int status)
{
	(void)status;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list_char	*command;
	t_list_char	**start;
	t_env		env;
	char		*cmd;

	(void)argc;
	(void)argv;
	env = env_tab_to_list(envp, &env);
	env.error_code = 0;
	while (1)
	{
		signal(SIGINT, signalhandler);
		signal(SIGQUIT, 0);
		cmd = readline("minishell> ");
		if (!cmd)
			exit (0);
		if (cmd[0] == '\0')
			continue ;
		add_history(cmd);
		cmd = replace_env_var(cmd, env);
		printf("---------\n%s\n", cmd);
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
