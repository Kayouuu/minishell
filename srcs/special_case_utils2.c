/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:44:20 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/23 10:48:15 by psaulnie         ###   ########.fr       */
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

static int	check_var(char *str)
{
	int	j;

	j = -1;
	while (str[++j])
	{
		if (str[j] == '=')
			break ;
		if (ft_isalnum(str[j]) != 1)
			return (1);
	}
	return (0);
}

int	export(char **list, t_env *env)
{
	int		i;
	int		j;
	char	*var;

	(void)env;
	i = 0;
	j = 0;
	if (!list[1])
	{
		export_no_arg(env);
		return (0);
	}
	while (list[++j])
	{
		if (list[j][0] == '=' || check_var(list[j]) == 1)
		{
			printf("export: `%s': not a valid identifier\n", list[j]);
			return (1);
		}
		while (list[j][i] && list[j][i] != '=')
			i++;
		var = ft_substr(list[j], 0, ++i);
		if (!var)
			return (1);
		env_replace_line(&env, var, &list[j][i]);
		free(var);
	}
	return (0);
}

static int	while_loop(char **list, int j)
{
	int	i;

	i = -1;
	while (list[j][++i])
	{
		if (list[j][i] < '!' || list[j][i] > '?')
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			return (1);
		}
	}
	return (0);
}

int	leave_this(char **list)
{
	int			i;
	long int	nbr;
	int			j;

	i = 1;
	j = 0;
	ft_putendl_fd("exit", 2);
	if (!list[1])
		exit (0);
	if (list[2])
	{
		if (while_loop(list, j++) == 1)
		{
			free_all(list);
			return (0);
		}
		exit (255);
	}
	else if (while_loop(list, 1) == 1)
		exit (255);
	nbr = ft_atoi(list[1]);
	free_all(list);
	if (nbr <= 0 && nbr >= 255)
		exit (nbr);
	else
		exit (nbr % 256);
}
