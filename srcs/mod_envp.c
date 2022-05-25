/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:36:03 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/25 14:54:38 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	shell_lvl(char **envp, t_env *env, t_list_char *start, int i)
{
	char	*str;

	str = ft_itoa((int)ft_atoi(&envp[i][6]) + 1);
	if (!str || !lstadd_back_char(&env->addon_env,
			lstnew_char(ft_strjoin("SHLVL=", str))))
	{
		if (str)
			free(str);
		lstclear_char(&start, free);
		error(1, "Malloc error");
	}
	free(str);
}

void	env_tab_to_list(char **envp, t_env *env)
{
	int			i;
	int			total;

	i = -1;
	total = 0;
	env->start = env->addon_env;
	while (envp[++i])
	{
		if (ft_memcmp(envp[i], "OLDPWD=", 7) != 0)
		{
			if (ft_memcmp(envp[i], "SHLVL=", 6) == 0)
				shell_lvl(envp, env, env->start, i);
			else if (!lstadd_back_char(&env->addon_env,
					lstnew_char(ft_strdup(envp[i]))))
			{
				lstclear_char(&env->start, free);
				error(1, "Malloc error");
			}
			total++;
		}
	}
	env->len_env = total;
}

char	**env_list_to_tab(t_env *env)
{
	int		i;
	char	**envp;

	i = -1;
	envp = malloc(sizeof(char *) * (env->len_env + 1));
	if (!envp)
		error(0, "");
	while (env->addon_env != NULL)
	{
		envp[++i] = env->addon_env->content;
		env->addon_env = env->addon_env->next;
	}
	envp[i] = NULL;
	return (envp);
}
