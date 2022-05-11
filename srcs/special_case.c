/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:02:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/11 12:18:37 by lbattest         ###   ########.fr       */
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

static int	check_flag(char *flag)
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

static char	*return_pwd(void)
{
	char	*cwd;

	cwd = getcwd((char *) NULL, 1);
	if (cwd == NULL)
	{
		ft_putendl_fd("minishell: Probleme with the path", 2);
		return (NULL);
	}
	return (cwd);
}

static void	cd_param(char **list, t_env *env)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (ft_memcmp(list[1], "--\0", 2) == 0)
		return ;
	if (ft_memcmp(list[1], "-\0", 2) == 0)
	{
		oldpwd = get_envvar(env, "OLDPWD=");
		if (oldpwd != NULL)
		{
			if (chdir(oldpwd) == -1)
				perror("minishell");
			printf("%s\n", oldpwd);
		}
		else
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return ;
	}
	else if (access(list[1], X_OK) == -1)
		perror("minishell");
	env_replace_line(env, "OLDPWD=", return_pwd());
	if (chdir(list[1]) == -1)
		perror("minishell");
	return ;
}

static void	go_to(char **list, t_env *env)
{
	if (list[1])
	{
		cd_param(list, env);
		if (ft_memcmp(list[1], "--\0", 2) == 0)
		{
			if (chdir(get_envvar(env, "HOME=")) == -1)
			{
				perror("minishell");
				return ;
			}
			env_replace_line(env, "OLDPWD=", return_pwd());
		}
		return ;
	}
	else
	{
		if (chdir(get_envvar(env, "HOME=")) == -1)
		{
			perror("minishell");
			return ;
		}
		env_replace_line(env, "OLDPWD=", return_pwd());
	}
	return ;
}

static void	write_env(t_env *env)
{
	t_list_char	*start;

	start = env->addon_env;
	while (env->addon_env)
	{
		printf("%s\n", env->addon_env->content);
		env->addon_env = env->addon_env->next;
	}
	env->addon_env = start;
	return ;
}
static void	export(char **list, t_env *env)
{
	// t_index	var;

	// var.i = 0;
	// while (list)
	(void)env;
	printf("%s\n", list[1]);
}

static void	export(char **list, t_env *env)
{
	;
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
	else if (ft_memcmp(list[0], "export\0", 7) == 0)
		export(list, env);
	// else if (ft_memcmp(list[0], "unset\0", 7) == 0)
	// 	env_remove_line(env, list[1]);
	else
	{
		free_all(list);
		return (0);
	}
	free_all(list);
	return (1);
}
