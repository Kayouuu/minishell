/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:10 by psaulnie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/06 13:50:14 by lbattest         ###   ########.fr       */
=======
/*   Updated: 2022/04/07 10:18:56 by psaulnie         ###   ########.fr       */
>>>>>>> 52dfc236890cf41175807752764165952ebbb324
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_list_char	*command;
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
		start_execution(&command, envp);
		lstclear_char(&command, free);
	}
	return (1);
}
