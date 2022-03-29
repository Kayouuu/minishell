/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/29 10:03:06 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_list_char	*command;
	char		*cmd;
	int			size;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		cmd = readline("\033[0;36mminishell> \033[0;37m");
		if (!cmd)
		{
			free(cmd);
			return (0);
		}
		size = count_size(cmd);
		if (size == -1)
			cmd = dquote(cmd, 0);
		if (size == -2)
			cmd = dquote(cmd, 1);
		add_history(cmd);
		command = parsing(cmd);
		replace_var_and_quote(command);
		free(cmd);
	}
	return (1);
}
