/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/21 13:53:39 by psaulnie         ###   ########.fr       */
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

t_list_char	*start_parsing(char *cmd, t_env *env)
{
	t_list_char	*command;

	cmd = replace_env_var(cmd, *env);
	command = parsing(cmd);
	free(cmd);
	split_redirection(&command, env);
	return (command);
}

static void	signalhandler(int status)
{
	(void)status;
	if (!g_signal_flags)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static t_env	while_main(t_env *env, char *cmd, t_list_char *command,
	t_list_char **start)
{
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	cmd = readline("minishell> ");
	if (!cmd)
		exit(1);
	g_signal_flags = 0;
	if (cmd[0] == '\0')
	{
		free(cmd);
		return (*env);
	}
	add_history(cmd);
	command = start_parsing(cmd, env);
	if (check_and_clean_parsing(&command) == 0)
		return (*env);
	start = &command;
	*env = start_execution(&command, env);
	clear_list(start);
	return (*env);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list_char	*command;
	t_list_char	**start;
	t_env		env;
	char		*cmd;

	(void)argc;
	(void)argv;
	env.addon_env = NULL;
	env_tab_to_list(envp, &env);
	env.error_code = 0;
	cmd = NULL;
	command = NULL;
	start = NULL;
	while (1)
		env = while_main(&env, cmd, command, start);
}
