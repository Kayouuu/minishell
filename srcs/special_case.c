/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:02:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/04 14:08:40 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	get_pwd(void)
{
	char	*cwd;

	cwd = getcwd((char *) NULL, 1);
	if (cwd == NULL)
	{
		ft_putendl_fd("minishell: Probleme with the path", 2);
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
	return ;
}

static void	write_loop(int i, char **list)
{
	while (list[++i])
	{
		printf("%s", list[i]);
		if (list[i + 1])
			printf(" ");
	}
}

static int check_flag(char *flag)
{
	int	i;

	i = 1;
	while (flag[++i])
		if (flag[i] != 'n')
			return (1);
	return (0);
}

static void	echo(char **list)
{
	int	i;

	if (list[1] && ft_memcmp(list[1], "-n", 2) == 0 && !check_flag(list[1]))
	{
		i = 1;
		if (list[2])
			write_loop(i, list);
	}
	else
	{
		i = 0;
		if (list[1])
			write_loop(i, list);
		printf("\n");
	}
}

//pas fini ca
static void	go_to(char **list, t_env *env)
{
	if (list[1])
	{
		if (ft_memcmp(list[1], "-\0", 2) == 0)
			;
		if (access(list[1], X_OK) == -1)
		{
			perror("minishell");
			return ;
		}
		if (chdir(list[1]) == -1)
		{
			perror("minishell");
			return ;
		}
	}
	else
	{
		if (chdir(get_envvar(env->envp, "HOME=")) == -1)
		{
			perror("minishell");
			return ;
		}
	}
}

static void write_env(t_env *env)
{
	int	i;

	i = -1;
	while (env->envp[++i])
		printf("%s\n", env->envp[i]);
	while (env->addon_env)
	{
		printf("%s\n", env->addon_env->content);
		env->addon_env = env->addon_env->next;
	}
	return ;
}

int	special_case(char **list, t_env *env)
{
	if (ft_memcmp(list[0], "pwd\0", 4) == 0)
		get_pwd();
	else if (ft_memcmp(list[0], "env\0", 4) == 0)
		write_env(env);
	else if (ft_memcmp(list[0], "exit\0", 5) == 0)
		exit(0);
	else if (ft_memcmp(list[0], "echo\0", 5) == 0)
		echo(list);
	else if (ft_memcmp(list[0], "cd\0", 3) == 0)
		go_to(list, env);
	// else if (ft_memcmp(list->content, "export\0", 7) == 0)
	// 	export();
	else
		return (0);
	free_all(list);
	return (1);
}
