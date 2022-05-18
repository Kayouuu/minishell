/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:36:03 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/18 16:09:42 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	shell_lvl(char **envp, t_env *env, t_list_char *start, int i)
{
	if (!lstadd_back_char(&env->addon_env,
			lstnew_char(ft_strjoin("SHLVL=",
					ft_itoa((int)ft_atoi(&envp[i][6]) + 1)))))
	{
		lstclear_char(&start, free);
		error(1, "Malloc error");
	}
}

void	env_tab_to_list(char **envp, t_env *env)
{
	int			i;
	int			total;
	t_list_char	*start;

	i = -1;
	total = 0;
	start = env->addon_env;
	while (envp[++i])
	{
		if (ft_memcmp(envp[i], "OLDPWD=", 7) != 0)
		{
			if (ft_memcmp(envp[i], "SHLVL=", 6) == 0)
				shell_lvl(envp, env, start, i);
			else if (!lstadd_back_char(&env->addon_env,
					lstnew_char(ft_strdup(envp[i]))))
			{
				lstclear_char(&start, free);
				error(1, "Malloc error");
			}
			total++;
		}
	}
	env->len_env = total;
	return ;
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
