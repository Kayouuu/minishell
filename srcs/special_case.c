/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:02:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/21 17:37:12 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_pwd(char **list)
{
	char	*cwd;

	if (list[1])
	{
		ft_putendl_fd("minishell: Too many arguments", 2);
		return (1);
	}
	cwd = getcwd((char *) NULL, 1);
	if (cwd == NULL)
	{
		ft_putendl_fd("minishell: Problem with the path", 2);
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

static void	write_loop(int i, char **list)
{
	while (list[++i])
	{
		printf("%s", list[i]);
		if (list[i + 1])
			printf(" ");
	}
}

static int	check_flag(char *flag)
{
	int	i;

	i = 1;
	while (flag[++i])
		if (flag[i] != 'n')
			return (1);
	return (0);
}

static void	echo(char **list)
{
	int	i;

	i = 1;
	if (list[i] && ft_memcmp(list[i], "-n", 2) == 0 && !check_flag(list[i]))
	{
		while (list[i] && ft_memcmp(list[i], "-n", 2) == 0
			&& !check_flag(list[i]))
			i++;
		if (list[i])
		{
			write_loop(i - 1, list);
			return ;
		}
	}
	else
	{
		if (list[i])
			write_loop(i - 1, list);
		printf("\n");
		return ;
	}
}

int	special_case(char **list, t_env *env)
{
	int	error;

	error = 0;
	if (list[0] && ft_memcmp(list[0], "pwd\0", 4) == 0)
		error = get_pwd(list);
	else if (list[0] && ft_memcmp(list[0], "env\0", 4) == 0)
		write_env(env);
	else if (list[0] && ft_memcmp(list[0], "echo\0", 5) == 0)
		echo(list);
	else if (list[0] && ft_memcmp(list[0], "cd\0", 3) == 0)
		error = go_to(list, env);
	else if (list[0] && ft_memcmp(list[0], "export\0", 7) == 0)
		error = export(list, env);
	else if (list[0] && ft_memcmp(list[0], "unset\0", 7) == 0)
		env_remove_line(env, list[1]);
	else if (list[0] && ft_memcmp(list[0], "exit\0", 7) == 0)
		error = leave_this(list);
	else
	{
		free_all(list);
		return (-1);
	}
	free_all(list);
	return (error);
}
