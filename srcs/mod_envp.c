/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:36:03 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/09 14:17:19 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	env_tab_to_list(char **envp, t_env *env)
{
	int		i;
	int		total;
	t_env	*start;

	start = env;
	i = -1;
	total = 0;
	while (envp[++i])
	{
		if (ft_memcmp(envp[i], "OLDPWD=", 7) != 0)
		{
			if (!lstadd_back_char(&env->addon_env, lstnew_char(envp[i])))
			{
				lstclear_char(&start->addon_env, free);
				error(1, "Malloc error");
			}
			total++;
		}
	}
	env->len_env = total;
	return (*env);
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
