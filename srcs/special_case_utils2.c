/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:44:20 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/18 17:22:09 by lbattest         ###   ########.fr       */
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
	env_replace_line(&env, var, &list[1][i]);
	free(var);
	return ;
}

void	leave_this(char **list)
{
	int			i;
	long int	nbr;

	i = -1;
	printf("%s\n", list[1]);
	while (list[1][++i])
	{
		//il manque des test car - + est aumoins good
		if (ft_isdigit(list[1][i]) == 0)
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
		exit(-1);
		//pas encore trouver
}
