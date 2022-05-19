/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:44:20 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/19 11:28:57 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_equal(char *str)
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

static void	export_no_arg(t_env *env)
{
	t_list_char	*start;

	start = env->addon_env;
	while (env->addon_env)
	{
		printf("declare -x %s\n", env->addon_env->content);
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
	{
		export_no_arg(env);
		return ;
	}
	while (list[1][i] && list[1][i] != '=')
		i++;
	var = ft_substr(list[1], 0, ++i);
	if (!var)
		return ;
	env_replace_line(&env, var, &list[1][i]);
	free(var);
}

void	leave_this(char **list)
{
	int			i;
	long int	nbr;

	i = -1;
	while (list[1][++i])
	{
		if (list[1][i] < '!' || list[1][i] > '?')
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			exit (255);
		}
	}
	nbr = ft_atoi(list[1]);
	free_all(list);
	if (nbr <= 0 && nbr >= 255)
		exit (nbr);
	else
		exit (nbr % 256);
}
