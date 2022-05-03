/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:53:18 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/03 16:08:57 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_envvar(char **envp, char *var)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_memcmp(envp[i], var, ft_strlen(var)) == 0)
			return (&envp[i][ft_strlen(var)]);
		i++;
	}
	return (NULL);
}

/*
	this function take envp and a char * with the name of the command(cat, ...)
	In the end exe is a char * with the path + the command(/bin/cat, ...)
*/

char	*get_path(char **envp, char *cmd)
{
	char	*exe;
	char	*path;
	char	**tmp;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_envvar(envp, "PATH=");
	if (!path)
		return (NULL);
	i = 0;
	tmp = ft_split(path, ':');
	while (tmp[i])
	{
		exe = ft_strjoin_mod(tmp[i], cmd);
		if (access(exe, X_OK | F_OK) == 0)
		{
			free_all(tmp);
			return (exe);
		}
		i++;
	}
	free_all(tmp);
	return (NULL);
}
