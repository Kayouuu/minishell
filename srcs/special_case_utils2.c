/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:44:20 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/12 11:45:59 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	write_env(t_env *env)
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

void	export(char **list, t_env *env)
{
	int		i;
	char	*var;

	(void)env;
	i = 0;
	if (!list[1])
		return ;
	while (list[1][i] && list[1][i] != '=')
		i++;
	var = ft_substr(list[1], 0, ++i);
	if (!var)
		return ;
	printf("var: %s\nvalue: %s\n", var, &list[1][i]);
	env_replace_line(&env, var, &list[1][i]);
	free(var);
	return ;
}
