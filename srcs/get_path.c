/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:53:18 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/21 18:30:02 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_envvar(t_env *env, char *var)
{
	t_list_char	*start;

	start = env->addon_env;
	while (env->addon_env->content != NULL)
	{
		if (ft_memcmp(env->addon_env->content, var, ft_strlen(var)) == 0)
			return (&env->addon_env->content[ft_strlen(var)]);
		if (env->addon_env->next)
			env->addon_env = env->addon_env->next;
		else
			break ;
	}
	env->addon_env = start;
	return (NULL);
}

/*
	this function take envp and a char * with the name of the command(cat, ...)
	In the end exe is a char * with the path + the command(/bin/cat, ...)
*/

char	*get_path(t_env *env, char *cmd)
{
	char	*exe;
	char	*path;
	char	**tmp;
	int		i;

	if (cmd[0] == '\0')
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_envvar(env, "PATH=");
	if (!path)
		return (NULL);
	i = -1;
	tmp = ft_split(path, ':');
	while (tmp[++i])
	{
		exe = ft_strjoin_mod(tmp[i], cmd);
		if (access(exe, X_OK | F_OK) == 0)
		{
			free_all(tmp);
			return (exe);
		}
	}
	free_all(tmp);
	return (NULL);
}
