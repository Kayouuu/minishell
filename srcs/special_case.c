/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:02:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/04/04 10:58:19 by psaulnie         ###   ########.fr       */
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

static void	echo(t_list_char *list)
{
	if (list->next != NULL)
	{
		list = list->next;
		if (ft_memcmp(list->content, "-n\0", 3) == 0)
		{		
			if (list->next != NULL)
			{
				list = list->next;
				printf("%s", list->content);
			}
		}
		else
			printf("%s\n", list->content);
	}
}
//pas fini ca
static void	go_to(t_list_char *list)
{
	if (list->next != NULL)
	{
		list = list->next;
		if (ft_memcmp(list->content, "-\0", 2) == 0)
		{

		}
		if (access(list->content, X_OK) == -1)
			error(0, "");
		if (chdir(list->content) == -1)
			error(0, "");
	}
}

void	special_case(t_list_char *list, char **envp)
{
	int	i;

	i = -1;
	if (ft_memcmp(list->content, "pwd\0", 4) == 0)
		get_pwd();
	else if (ft_memcmp(list->content, "env\0", 4) == 0)
		while (envp[++i])
			printf("%s\n", envp[i]);
	else if (ft_memcmp(list->content, "exit\0", 5) == 0)
		exit(0);
	else if (ft_memcmp(list->content, "echo\0", 5) == 0)
		echo(list);
	else if (ft_memcmp(list->content, "cd\0", 3) == 0)
		go_to(list);
	// else if (ft_memcmp(list->content, "export\0", 7) == 0)
	// 	export();
}