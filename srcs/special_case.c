/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:02:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/04/12 13:28:28 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	get_pwd(void)
{
	char	*cwd;

	cwd = getcwd((char *) NULL, 1);
	if (cwd == NULL)
		error(1, "minishell: Probleme with the path");
	printf("%s\n", cwd);
	free(cwd);
	return ;
}

static void	echo(char **list)
{
	if (list[1] && ft_memcmp(list[1], "-n\0", 3) == 0)
	{
		if (list[2])
			printf("%s", list[2]);
		else
			printf("");
	}
	else
	{
		if (list[1])
			printf("%s\n", list[1]);
		else
			printf("\n");
	}
}

//pas fini ca
static void	go_to(char **list)
{
	if (ft_memcmp(list[1], "-\0", 2) == 0)
		;
	if (access(list[1], X_OK) == -1)
		error(0, "");
	if (chdir(list[1]) == -1)
		error(0, "");
}

int	special_case(char **list, char **envp, t_list_char **start)
{
	int	i;

	i = -1;
	if (ft_memcmp(list[0], "pwd\0", 4) == 0)
		get_pwd();
	else if (ft_memcmp(list[0], "env\0", 4) == 0)
		while (envp[++i])
			printf("%s\n", envp[i]);
	else if (ft_memcmp(list[0], "exit\0", 5) == 0)
		exit(0);
	else if (ft_memcmp(list[0], "echo\0", 5) == 0)
		echo(list);
	else if (ft_memcmp(list[0], "cd\0", 3) == 0)
		go_to(list);
	// else if (ft_memcmp(list->content, "export\0", 7) == 0)
	// 	export();
	else
		return (1);
	free_all(list);
	lstclear_char(start, free);
	exit(0);
}
