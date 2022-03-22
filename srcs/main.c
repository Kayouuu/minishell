/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/22 10:01:21 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_list_char	*command;
	char		*cmd;

	(void)argc;
	(void)argv;
	while (1)
	{
		cmd = readline("\033[0;36mminishell> \033[0;37m");
		add_history(cmd);
		command = parsing(cmd);
		replace_var_and_quote(command, envp);
		free(cmd);
	}
	return (1);
}
