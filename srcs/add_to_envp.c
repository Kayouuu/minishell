/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:41:36 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/01 12:48:19 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*find_equal(char *to_add)
{
	int		i;
	int		equal;
	t_index	index;

	equal = 0;
	i = -1;
	index.d_quote = 0;
	index.s_quote = 0;
	while (to_add[++i] != '=' && to_add[i])
	{
		if (ft_isalnum(to_add[i]) != 1)
			error(1, "export: not valid identifier");
		if (to_add[i + 1] == '=')
			equal = i + 1;
	}
	if (equal == 0)
		return (to_add);
	else
	{
		while (to_add[++i])
		{
			if (to_add[i] == '\"')
				index.d_quote ^= 1;
			else if (to_add[i] == '\'')
				index.s_quote ^= 1;
			if ((index.s_quote == 0 || index.d_quote == 0)
				&& ft_isalnum(to_add[i]) != 1)
				error(1, "export: not valid identifier");
		}
	}
	return (to_add);
}

void	add_env(t_env *env, char *to_add)
{
	int		i;
	size_t	equal;
	char	*clean;

	i = -1;
	equal = 0;
	(void)env;
	clean = find_equal(to_add);
	lstadd_back_char(&env->addon_env, lstnew_char(ft_strjoin_gnl(to_add, "\n")));
	puts("help");
	if (equal - 1 == ft_strlen(to_add))
	{
		puts("pas de =");
		//il n'y a pas de egal donc faut juste rajouer un \n
	}
	printf("%zu\n", equal);
	return ;
}
