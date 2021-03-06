/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:44:20 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/30 11:38:40 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

void	write_env(t_env *env)
{
	t_list_char	*start;

	start = env->addon_env;
	while (env->addon_env)
	{
		if (is_equal(env->addon_env->content) == 1)
			printf("%s\n", env->addon_env->content);
		env->addon_env = env->addon_env->next;
	}
	env->addon_env = start;
	return ;
}

static int	check_var(char *str)
{
	int	j;
	int	contain_char;

	j = -1;
	contain_char = 0;
	while (str[++j])
	{
		if (str[j] == '=')
			break ;
		if (ft_isalpha(str[j]))
			contain_char = 1;
		if (ft_isalnum(str[j]) != 1)
			return (1);
	}
	if (contain_char)
		return (0);
	return (1);
}

static int	while_loop(char *var, char **list, t_index *index, t_env *env)
{
	if (list[index->j][0] == '=' || check_var(list[index->j]) == 1)
		return ((ft_putendl_fd("export: not a valid identifier", 2)));
	while (list[index->j][index->i] && list[index->j][index->i] != '=')
		index->i++;
	if (list[index->j][index->i] == '=')
	{
		var = ft_substr(list[index->j], 0, index->i);
		if (!var)
			return (1);
		env_remove_line(env, var);
		free(var);
		index->i++;
	}
	var = ft_substr(list[index->j], 0, index->i);
	if (!var)
		return (1);
	env_replace_line(&env, var, &list[index->j][index->i]);
	free(var);
	return (0);
}

int	export(char **list, t_env *env)
{
	t_index		index;
	char		*var;
	t_list_char	*start;

	index.i = 0;
	index.j = 0;
	var = NULL;
	if (!list[1])
	{
		start = env->addon_env;
		while (env->addon_env)
		{
			printf("declare -x %s\n", env->addon_env->content);
			env->addon_env = env->addon_env->next;
		}
		env->addon_env = start;
		return (0);
	}
	while (list[++index.j])
		if (while_loop(var, list, &index, env) == 1)
			return (1);
	return (0);
}
