/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:38:04 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/21 14:06:52 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	cd_minus(t_env *env)
{
	char		*oldpwd;
	t_list_char	*start;

	start = env->addon_env;
	oldpwd = get_envvar(env, "OLDPWD=");
	if (oldpwd != NULL)
	{
		if (chdir(oldpwd) == -1)
		{
			perror("minishell");
			return (1);
		}
		printf("%s\n", oldpwd);
	}
	else
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	env->addon_env = start;
	return (0);
}

static int	cd_param(char **list, t_env *env)
{
	char		*pwd;

	if (ft_memcmp(list[1], "--\0", 2) == 0)
		return (0);
	else if (ft_memcmp(list[1], "-\0", 2) == 0)
	{
		if (cd_minus(env) == 1)
			return (1);
		return (0);
	}
	else if (access(list[1], X_OK) == -1)
	{
		perror("minishell");
		return (1);
	}
	pwd = return_pwd();
	env_replace_line(&env, "OLDPWD=", pwd);
	free(pwd);
	if (chdir(list[1]) == -1)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}

static int	cd_args(char **list, t_env *env, t_list_char *start, char *pwd)
{
	if (cd_param(list, env) == 1)
		return (1);
	if (ft_memcmp(list[1], "--\0", 2) == 0)
	{
		pwd = return_pwd();
		env_replace_line(&env, "OLDPWD=", pwd);
		free(pwd);
		if (chdir(get_envvar(env, "HOME=")) == -1)
		{
			perror("minishell");
			return (1);
		}
	}
	env->addon_env = start;
	return (0);
}

int	go_to(char **list, t_env *env)
{
	char		*pwd;
	t_list_char	*start;

	start = env->addon_env;
	pwd = NULL;
	if (list[1])
	{
		if (list[1][0] != '\0' && cd_args(list, env, start, pwd) == 1)
			return (1);
		return (0);
	}
	else
	{
		pwd = return_pwd();
		env_replace_line(&env, "OLDPWD=", pwd);
		if (chdir(get_envvar(env, "HOME=")) == -1)
		{
			perror("minishell");
			free(pwd);
			return (1);
		}
		free(pwd);
	}
	env->addon_env = start;
	return (0);
}

char	*return_pwd(void)
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
