/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:54:50 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/24 10:04:51 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_num(char **list, int j)
{
	int	i;

	i = -1;
	while (list[j][++i])
	{
		if (list[j][i] < '!' || list[j][i] > '9')
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			return (1);
		}
	}
	return (0);
}

static int	check_list(char **list)
{
	if (list[2])
	{
		ft_putendl_fd("minishell: too many arguments", 2);
		return (1);
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
	else
	{
		if (check_num(list, 1) == 0)
		{
			if (check_list(list))
				return (1);
			nbr = ft_atoi(list[1]);
			free_all(list);
			if (nbr <= 0 && nbr >= 255)
				exit (nbr);
			else
				exit (nbr % 256);
		}
		free_all(list);
		exit(255);
	}
}
