/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:38:04 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/12 11:52:51 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	cd_minus(t_env *env)
{
	char		*oldpwd;
	t_list_char	*start;

	start = env->addon_env;
	oldpwd = get_envvar(env, "OLDPWD=");
	if (oldpwd != NULL)
	{
		if (chdir(oldpwd) == -1)
			perror("minishell");
		printf("%s\n", oldpwd);
	}
	else
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	env->addon_env = start;
	return ;
}

static void	cd_param(char **list, t_env *env)
{
	char		*pwd;

	if (ft_memcmp(list[1], "--\0", 2) == 0)
		return ;
	else if (ft_memcmp(list[1], "-\0", 2) == 0)
	{
		cd_minus(env);
		return ;
	}
	else if (access(list[1], X_OK) == -1)
		perror("minishell");
	pwd = return_pwd();
	env_replace_line(&env, "OLDPWD=", pwd);
	free(pwd);
	if (chdir(list[1]) == -1)
		perror("minishell");
	return ;
}

static void	cd_args(char **list, t_env *env, t_list_char *start, char *pwd)
{
	cd_param(list, env);
	if (ft_memcmp(list[1], "--\0", 2) == 0)
	{
		pwd = return_pwd();
		env_replace_line(&env, "OLDPWD=", pwd);
		free(pwd);
		if (chdir(get_envvar(env, "HOME=")) == -1)
		{
			perror("minishell");
			return ;
		}
	}
	env->addon_env = start;
	return ;
}

void	go_to(char **list, t_env *env)
{
	char		*pwd;
	t_list_char	*start;

	start = env->addon_env;
	pwd = NULL;
	if (list[1])
	{
		cd_args(list, env, start, pwd);
		return ;
	}
	else
	{
		if (chdir(get_envvar(env, "HOME=")) == -1)
		{
			perror("minishell");
			return ;
		}
		pwd = return_pwd();
		env_replace_line(&env, "OLDPWD=", pwd);
		free(pwd);
	}
	env->addon_env = start;
	return ;
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
