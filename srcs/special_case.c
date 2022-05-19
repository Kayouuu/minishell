/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:02:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/19 14:27:53 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_pwd(void)
{
	char	*cwd;

	cwd = getcwd((char *) NULL, 1);
	if (cwd == NULL)
	{
		ft_putendl_fd("minishell: Probleme with the path", 2);
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

	if (list[1] && ft_memcmp(list[1], "-n", 2) == 0 && !check_flag(list[1]))
	{
		i = 1;
		if (list[2])
			write_loop(i, list);
	}
	else
	{
		i = 0;
		if (list[1])
			write_loop(i, list);
		printf("\n");
	}
}

int	special_case(char **list, t_env *env)
{
	int	error;

	error = 0;
	if (list[0] && ft_memcmp(list[0], "pwd\0", 4) == 0)
	{
		error = get_pwd();
		if (error == 1)
			return (error);
	}
	else if (list[0] && ft_memcmp(list[0], "env\0", 4) == 0)
		write_env(env);
	else if (list[0] && ft_memcmp(list[0], "echo\0", 5) == 0)
		echo(list);
	else if (list[0] && ft_memcmp(list[0], "cd\0", 3) == 0)
	{
		error = go_to(list, env);
		if (error == 1)
			return (error);
	}
	else if (list[0] && ft_memcmp(list[0], "export\0", 7) == 0)
	{
		error = export(list, env);
		if (error == 1)
			return (1);
	}
	else if (list[0] && ft_memcmp(list[0], "unset\0", 7) == 0)
		env_remove_line(env, list[1]);
	else if (list[0] && ft_memcmp(list[0], "exit\0", 7) == 0)
		leave_this(list);
	else
	{
		free_all(list);
		return (-1);
	}
	free_all(list);
	return (error);
}
