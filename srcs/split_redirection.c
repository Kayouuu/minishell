/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:11:59 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/13 15:59:11 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	Split the command in the array
	Example : [echo a > test b] ---> [echo a b] [> test]
*/

// static t_list_char	*insert_new_link(t_index var, char *cmd,
// 		t_list_char **start)
// {
// 	char		*str;
// 	t_list_char	*new_link;
// 	str = ft_stridup(cmd, var.i, var.j);
// 	if (!str)
// 	{
// 		lstclear_char(start, free);
// 		exit_error_msg("Malloc error");
// 	}
// 	new_link = lstnew_char(str);
// 	if (!new_link)
// 	{
// 		free(str);
// 		lstclear_char(start, free);
// 		exit_error_msg("Malloc error");
// 	}
// 	return (new_link);
// }

static int	iteration_nbr(char *cmd)
{
	t_index	var;
	int		nbr;

	var.i = 0;
	var.quote = '0';
	var.quotes = 0;
	nbr = 0;
	while (cmd != NULL && cmd[var.i])
	{
		if (cmd[var.i] == '\'' && (var.quotes == '0'))
			var.quote = '\'';
		if (cmd[var.i] == '"' && (var.quotes == '0'))
			var.quote = '"';
		if (cmd[var.i] == var.quotes)
			var.quotes++;
		if (var.quotes == 2)
		{
			var.quote = '0';
			var.quotes = 0;
		}
		if ((cmd[var.i] == '<' || cmd[var.i] == '>') && (var.quote == '0'))
			nbr++;
		var.i++;
	}
	return (nbr);
}

static char	*redirection_split(char *cmd)
{
	size_t	i;
	char	c[2];
	char	*new_str;

	c[0] = cmd[0];
	c[1] = '\0';
	i = 0;
	while (cmd[i] && (cmd[i] == '<' || cmd[i] == '>'))
	{
		if (i == 0)
			new_str = ft_strdup(c);
		else
			new_str = ft_strjoin_gnl(new_str, c);
		if (!new_str)
			exit_error_msg("Malloc error");
		i++;
	}
	free(cmd);
	return (new_str);
}

static t_index	skipper(t_index var, char *cmd)
{
	while (cmd != NULL && cmd[var.i] && (cmd[var.i] != '<' && cmd[var.i] != '>'
			&& var.quotes % 2 == 0))
	{
		if (cmd[var.i] == '\'' && (var.quotes == '0'))
			var.quote = '\'';
		if (cmd[var.i] == '"' && (var.quotes == '0'))
			var.quote = '"';
		if (cmd[var.i] == var.quotes)
			var.quotes++;
		if (var.quotes == 2)
		{
			var.quote = '0';
			var.quotes = 0;
		}
		var.i++;
	}
	var.j = var.i;
	while (cmd != NULL && cmd[var.j] && !ft_iswhitespace(cmd[var.j]))
		var.j++;
	return (var);
}

static int	set_redirection_type(char *redirection)
{
	if (!ft_memcmp(redirection, "<\0", 2))
		return (SINGLE_RIN);
	else if (!ft_memcmp(redirection, "<<\0", 3))
		return (DOUBLE_RIN);
	else if (!ft_memcmp(redirection, ">\0", 2))
		return (SINGLE_ROUT);
	else if (!ft_memcmp(redirection, ">>\0", 3))
		return (DOUBLE_ROUT);
	else
	{
		printf("Parse error to handle and free without leaks\n");
		exit (0);
	}
}

static void	splitter(t_list_char **start, t_list_char **cmd)
{
	int			iteration;
	int			current;
	char		*str;
	char		*redirection;
	int			j;
	t_index		var;

	iteration = iteration_nbr((*cmd)->content);
	current = 0;
	(*cmd)->type = malloc(sizeof(int) * (iteration + 1));
	(*cmd)->redirection_file = malloc(sizeof(char *) * (iteration + 1));
	if (!(*cmd)->redirection_file || !(*cmd)->type)
		exit_error_msg("Malloc error");
	while ((*cmd)->content != NULL && current < iteration)
	{
		var.i = 0;
		var.quote = '0';
		var.quotes = 0;
		var = skipper(var, (*cmd)->content);
		if ((*cmd)->content[var.j])
			var.j++;
		if ((*cmd)->content[var.j])
			while ((*cmd)->content[var.j] && !ft_iswhitespace((*cmd)->content[var.j]))
				var.j++;
		str = ft_stridup((*cmd)->content, var.i, var.j);
		if (!str)
		{
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
		redirection = redirection_split(str);
		(*cmd)->type[current] = set_redirection_type(redirection);
		j = var.i; // peut etre ici lol
		while ((*cmd)->content[j] && ((*cmd)->content[j] == '>' || (*cmd)->content[j] == '<'))
			j++;
		j = skip_whitespace((*cmd)->content, j);
		(*cmd)->redirection_file[current] =  ft_stridup((*cmd)->content, j, var.j + 1);
		if (var.i == 0)
			(*cmd)->content = NULL;
		else
		{
			(*cmd)->content = ft_strcut((*cmd)->content, var.i, var.j - 1);
			if (!(*cmd)->content || !(*cmd)->redirection_file[current])
			{
				lstclear_char(start, free);
				exit_error_msg("Malloc error");
			}
		}
		current++;
	}
	(*cmd)->type[current] = -1;
	(*cmd)->redirection_file[current] = NULL;
	for (int i = 0; (*cmd)->type[i] != -1; i++)
		printf("[%d] [%s]\n", (*cmd)->type[i], (*cmd)->redirection_file[i]);
}

void	split_redirection(t_list_char **cmd)
{
	t_list_char	*start;

	start = *cmd;
	while (*cmd != NULL)
	{
		(*cmd)->content = ft_strtrim((*cmd)->content, " \t\n\b\f");
		splitter(&start, cmd);
		(*cmd) = (*cmd)->next;
	}
	// split_redirection_and_filename(&start);
	remove_useless_command(&start);
	*cmd = start;
}
