/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:55 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/22 12:59:54 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_index
{
	int		i;
	int		j;
	int		s_quote;
	int		d_quote;
	char	quote;
	int		quotes;
}	t_index;

typedef struct s_env
{
	char		**envp;
	t_list_char	*addon_env;
}				t_env;

/*****************************************
 *										 *
 * 				  PARSING                *
 * 										 *
 *****************************************/

/*	DQUOTE.C	*/

char		*dquote(char *cmd, int arg);

/*	PARSING.C	*/

t_list_char	*parsing(char *cmd);

/*	PARSING_UTILS.C	*/

int			skip_whitespace(char *cmd, int i);
int			is_useless(char *command);

/*	QUOTE_REMOVER.C	*/

char		*remove_quote(t_list_char **start, char *cmd);
int			count_size(char *cmd);

/*	REPLACE_VAR_AND_QUOTE.C	*/

t_list_char	*replace_var_and_quote(t_list_char *cmd, char *envp[]);

#endif